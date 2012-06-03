<?php

/**
 * @file Database API for node_announce
 *
 */

/**
 * Function to load a node_announce by id
 * @param
 *  id
 */

function node_announce_load($id) {
  if ($id) {
    return db_select('node_announce', 'na')
      ->fields('na')
      ->condition('id', $id, '=')
      ->execute()
      ->fetchObject();
  } else {
    return NULL;
  }
}


function node_announce_list() {
  $results = array();
  $r = db_select('node_announce', 'na')
    ->fields('na')
    ->orderBy('date_field')
    ->orderBy('days_before')
    ->execute();

  foreach ($r as $obj) {
    $results[] = $obj;
  }

  return $results;
}

/**
 * Function to save a node announce, could be new or old
 *
 */
function node_announce_save(&$announce) {
  $announce_current = node_announce_load($announce->id);
  if ($announce_current) {
    return drupal_write_record('node_announce', $announce, 'id');
  } else {
    return drupal_write_record('node_announce', $announce);
  }
}

function node_announce_delete_records_by_nid($nid) {
  # db_query("DELETE FROM {node_announce_records} where nid=%d", $nid);
  db_delete('node_announce_records')
    ->condition('nid', $nid)
    ->execute();
}

function node_announce_delete_records_by_aid($aid) {
  # db_query("DELETE FROM {node_announce_records} where aid=%d", $aid);
  db_delete('node_announce_records')
    ->condition('aid', $aid)
    ->execute();
}

function node_announce_delete($aid) {
  node_announce_delete_records_by_aid($aid);
  # db_query("DELETE FROM {node_announce} where id=%d", $aid);
  db_delete('node_announce')
    ->condition('id', $aid)
    ->execute();
}

/**
 * This returns a list of date field options
 */

function node_announce_date_field_options() {
  $fields = array();

  $query = db_select('node_type', 'n');
  $query->join('field_config_instance', 'fci', 'fci.bundle=n.type');
  $query->join('field_config', 'fc', 'fci.field_id=fc.id');

  $results = $query->fields('n', array('name', 'type'))
    ->fields('fc', array('field_name'))
    ->fields('fci', array('data'))
    ->condition('fc.module', 'date')
    ->execute();

  // TODO: get the field label out of the fci.data
  foreach ($results as $obj) {
    $fields[$obj->type . ":" . $obj->field_name] = $obj->name . " - " . $obj->field_name;
  }
  return $fields;
}

/**
 * Pretty name for date field
 */
function node_announce_date_field_pretty($field) {
  $fields = node_announce_date_field_options();
  return $fields[$field];
}

/**
 *
 * QUERY that we are looking for
 SELECT *
FROM  `content_field_meeting_date` ,  `node`
WHERE node.type =  'meeting'
AND node.nid = content_field_meeting_date.nid
AND content_field_meeting_date.field_meeting_date_value > NOW( )
ORDER BY content_field_meeting_date.field_meeting_date_value ASC , content_field_meeting_date.vid DESC


 */

function node_announce_next_match($ann, $before = FALSE) {
  $array = explode(":", $ann->date_field);
  $type = $array[0];
  $field = $array[1];
  $fv = $field . "_value";

  /*  if (!$before) { */
  /*   $clause = "> NOW() ORDER BY c.$fv ASC"; */
  /* } else { */
  /*   $clause = "< NOW() ORDER BY c.$fv DESC"; */
  /* } */

  /* $r = db_query("SELECT n.nid from {content_$field} c, {node} n WHERE n.type='%s' AND n.nid = c.nid AND c.$fv $clause", $type); */

  $query = db_select('field_data_' . $field, 'f');
  $query->join('node', 'n', 'n.nid = f.entity_id');
  $query->fields('n', 'nid')->condition('n.type', $type);

  if (!$before) {
    $query->condition('f.' . $fv, 'NOW()', '>')
      ->orderBy('f.' . $fv, 'ASC');
  } else {
    $query->condition('f.' . $fv, 'NOW()', '<')
      ->orderBy('f.' . $fv, 'DESC');
  }
  $obj = $query->execute()->fetchObject();
  if (!$obj) {
    return NULL;
  }
  $node = node_load($obj->nid);
  return $node;
}

/**
 *
 *  For a given announce, figure out which nodes are in the time window. This requires selecting by node type
 */

function node_announce_applicable_nodes($ann) {
  $array = explode(":", $ann->date_field);
  $type = $array[0];
  $field = $array[1];
  $fv = $field . "_value";
  $nodes = array();

  $before = strftime("%Y-%m-%d %H:%M", time() + 24*60*60 * ($ann->days_before - 1));
  $after = strftime("%Y-%m-%d %H:%M", time() + 24*60*60 * ($ann->days_before + 1));

  drupal_set_message("SELECT n.nid from {content_$field} c, {node} n WHERE n.type='$type' AND n.nid = c.nid AND c.$fv > '$before' AND c.$fv < '$after'");

  $r = db_query("SELECT n.nid from {content_$field} c, {node} n WHERE n.type='%s' AND n.nid = c.nid AND c.$fv > '%s' AND c.$fv < '%s'", $type, $before, $after);
  while($nid = db_fetch_object($r)) {
    $node = node_load($nid->nid);
    $nodes[] = $node;
  }
  return $nodes;
}

/**
 * TODO: Repeating events are going to need more work
 */

function node_announce_already_announced($ann, $node) {
  $obj = db_select("node_announce_records", "n")
    ->fields('n', array('last_sent'))
    ->condition("nid", $node->nid)
    ->condition("aid", $ann->id)
    ->execute()
    ->fetchObject();
  #  $row = db_fetch_object(db_query("SELECT last_sent from {node_announce_records} n WHERE n.nid=%d and n.aid=%d", $node->nid, $ann->id));
  if ($obj) {
    return $obj->last_sent;
  } else {
    return NULL;
  }
}

function node_announce_load_records($aid) {
  $result = db_select("node_announce_records", "n")
    ->fields('n')
    ->condition('aid', $aid)
    ->orderBy('last_sent', 'DESC')
    ->execute();
  # $r = db_query("SELECT * FROM {node_announce_records} where aid=%d ORDER by last_sent DESC", $aid);
  $records = array();
  foreach ($result as $record) {
    $record->node = node_load($record->nid);
    $record->url = url(drupal_get_path_alias('node/' . $record->nid), array('absolute' => TRUE));
    $record->when = format_date($record->last_sent);
    $records[] = $record;
  }
  return $records;
}

function node_announce_record_send($aid, $nid) {
  $obj = (object)array(
                       "nid" => $nid,
                       "aid" => $aid,
                       "last_sent" => time()
                       );
  drupal_write_record('node_announce_records', $obj);
}