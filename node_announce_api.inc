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

/**
 * Function to save a node announce, could be new or old
 *
 */
function node_announce_save(&$announce) {
    $announce_current = node_announce_load($announce->id);
    if ($announce_current) {
        drupal_write_record('node_announce', $announce, 'id');
    } else {
        drupal_write_record('node_announce', $announce);
    }
}

/**
 *
 *  For a given announce, figure out which nodes are in the time window. This requires selecting by node type
 */

function node_announce_applicable_nodes($ann) {

}