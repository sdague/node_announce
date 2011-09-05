<?php

/**
 * @file
 * This provides the admin interface for node_announce
 */

function node_announce_form_list(&$form_state) {
  _node_announce_load_api();

  $form = array();
  $form['introduction'] = array(
    '#value' => t('Below are a list of active announcements.')
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Node add announcements
 */

function node_announce_form_add($form_state) {
  _node_announce_load_api();
  $ann = (object)$form_state['values'];

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $ann->id
  );
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#description' => t('Name for this announcement')
  );

  $form['date_field'] = array(
    '#title' => t('Node type / Date field'),
    '#type' => 'select',
    '#options' => node_announce_date_field_options(),
    '#description' => t('The node type and datefield to trigger the announce on')
  );

  $form['subject'] = array(
    '#title' => t('Announce Subject'),
    '#type' => 'textfield',
  );

  $form['body'] = array(
    '#title' => t('Announce Text'),
    '#type' => 'textarea',
  );

  $form['checkout']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}



function theme_node_announce_list() {

}