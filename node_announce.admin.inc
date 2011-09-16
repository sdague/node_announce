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

  $announces = node_announce_list();

  $form['content'] = array(
    '#value' => theme('node_announce_list', $announces)
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

  $form['schedule'] = array(
    '#title' => t('Announce Schedule (Days before event)'),
    '#type' => 'textfield',
    '#description' => t('Number of Days prior to event to send announce'),
  );

  $form['email_from'] = array(
    '#title' => t('Sender Email'),
    '#type' => 'textfield',
    '#description' => t('Email address of sender')
  );

  $form['email_to'] = array(
    '#title' => t('Recipient Email'),
    '#type' => 'textfield',
    '#description' => t('Email address of sender')
  );

  $form['subject'] = array(
    '#title' => t('Announcement Subject'),
    '#type' => 'textfield',
  );

  $form['message'] = array(
    '#title' => t('Announcement Text'),
    '#type' => 'textarea',
  );

  if (module_exists('token')) {
    $form['view']['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      //      '#description' => t('Prefer raw-text replacements for text to avoid problems with HTML entities!'),
    );

    $form['view']['token_help']['help'] = array(
      '#value' => theme('token_help', 'node'),
    );
  }

  $form['checkout']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}

function node_announce_form_add_validate($form, &$form_state) {
  if (!$form_state['values']['name']) {
    form_set_error('name', t('Name can not be blank'));
  }
  if (($form_state['values']['schedule'] == 0) || !preg_match("/^\d+$/", $form_state['values']['schedule'])) {
    form_set_error('schedule', t('Days must be a positive integer'));
  }
  if (!valid_email_address($form_state['values']['email_from'])) {
    form_set_error('email_from', t('Email from must be valid email address'));
  }
  if (!valid_email_address($form_state['values']['email_to'])) {
    form_set_error('email_to', t('Email to must be valid email address'));
  }
}

function node_announce_form_add_submit($form_id, &$form_state) {
  _node_announce_load_api();

  $obj = (object)$form_state['values'];

  if(node_announce_save($obj)) {
    drupal_set_message(t('Successfully created announcment: @name',
        array('@name' => $obj->name)));
  } else {
    drupal_set_message(t('Failed to create announcment: @name',
        array('@name' => $obj->name)), 'error');
  }
  $form_state['redirect'] = 'admin/settings/node_announce/list';
}
