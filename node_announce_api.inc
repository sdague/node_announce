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
        return db_fetch_object(db_query("SELECT * from {node_announce} where id = %d", $id));
    } else {
        return NULL;
    }
}


function node_announce_list() {
  $results = array();
  $r = db_query("SELECT * from {node_announce} ORDER BY date_field, days_before");
  while($obj = db_fetch_object($r)) {
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

/**
 * This returns a list of date field options
 */

function node_announce_date_field_options() {
  $fields = array();
  $results = db_query("SELECT c.type_name, c.field_name, c.label, n.name from {content_node_field_instance} c INNER JOIN {node_type} n ON c.type_name=n.type where c.widget_module='date' ORDER BY n.name, c.label");
  while($obj = db_fetch_object($results)) {
    $fields[$obj->type_name . ":" . $obj->field_name] = $obj->name . " - " . $obj->label;
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

  if (!$before) {
    $clause = "> NOW() ORDER BY c.$fv ASC";
  } else {
    $clause = "< NOW() ORDER BY c.$fv DESC";
  }

  $r = db_query("SELECT n.nid from {content_$field} c, {node} n WHERE n.type='%s' AND n.nid = c.nid AND c.$fv $clause, c.vid DESC", $type);
  $nid = db_fetch_object($r);
  $node = node_load($nid->nid);
  return $node;
}


/* function node_announce_find_preview_node($ann) { */
/*   db_query("SELECT n.nid FROM {node */
/* } */

/**
 *
 *  For a given announce, figure out which nodes are in the time window. This requires selecting by node type
 */

function node_announce_applicable_nodes($ann) {

}