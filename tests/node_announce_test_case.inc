<?php

class NodeAnnounceTestCase extends DrupalWebTestCase {
  /**
   * This tests to ensure that I've created the links that I expect using the
   * label attribute on them. It's a bit nicer than the text checking.
   */

  public $format = "Y-m-d H:i";

  public function createDateField() {
    # TODO: update to drupal 7 version... which is going to take a while

    /* $datefield = array ( */
    /*   'field_name' => 'field_meeting_date', */
    /*   'type_name' => 'meeting', */
    /*   'display_settings' => */
    /*   array ( */
    /*     'weight' => '-4', */
    /*     'parent' => '', */
    /*     'label' => */
    /*     array ( */
    /*       'format' => 'inline', */
    /*     ), */
    /*     'teaser' => */
    /*     array ( */
    /*       'format' => 'default', */
    /*       'exclude' => 0, */
    /*     ), */
    /*     'full' => */
    /*     array ( */
    /*       'format' => 'default', */
    /*       'exclude' => 0, */
    /*     ), */
    /*     4 => */
    /*     array ( */
    /*       'format' => 'default', */
    /*       'exclude' => 0, */
    /*     ), */
    /*     5 => */
    /*     array ( */
    /*       'format' => 'default', */
    /*       'exclude' => 0, */
    /*     ), */
    /*     'token' => */
    /*     array ( */
    /*       'format' => 'default', */
    /*       'exclude' => 0, */
    /*     ), */
    /*   ), */
    /*   'widget_active' => '1', */
    /*   'type' => 'date', */
    /*   'required' => '1', */
    /*   'multiple' => '1', */
    /*   'db_storage' => '0', */
    /*   'module' => 'date', */
    /*   'active' => '1', */
    /*   'locked' => '0', */
    /*   'columns' => */
    /*   array ( */
    /*     'value' => */
    /*     array ( */
    /*       'type' => 'varchar', */
    /*       'length' => 20, */
    /*       'not null' => false, */
    /*       'sortable' => true, */
    /*       'views' => true, */
    /*     ), */
    /*     'value2' => */
    /*     array ( */
    /*       'type' => 'varchar', */
    /*       'length' => 20, */
    /*       'not null' => false, */
    /*       'sortable' => true, */
    /*       'views' => false, */
    /*     ), */
    /*     'rrule' => */
    /*     array ( */
    /*       'type' => 'text', */
    /*       'not null' => false, */
    /*       'sortable' => false, */
    /*       'views' => false, */
    /*     ), */
    /*   ), */
    /*   'granularity' => */
    /*   array ( */
    /*     'year' => 'year', */
    /*     'month' => 'month', */
    /*     'day' => 'day', */
    /*     'hour' => 'hour', */
    /*     'minute' => 'minute', */
    /*   ), */
    /*   'timezone_db' => 'UTC', */
    /*   'tz_handling' => 'site', */
    /*   'todate' => 'optional', */
    /*   'repeat' => 1, */
    /*   'repeat_collapsed' => '1', */
    /*   'default_format' => 'default', */
    /*   'widget' => */
    /*   array ( */
    /*     'default_value' => 'now', */
    /*     'default_value_code' => '', */
    /*     'default_value2' => 'same', */
    /*     'default_value_code2' => '', */
    /*     'input_format' => 'Y-m-d H:i:s', */
    /*     'input_format_custom' => '', */
    /*     'increment' => '15', */
    /*     'text_parts' => */
    /*     array ( */
    /*     ), */
    /*     'year_range' => '-7:+3', */
    /*     'label_position' => 'above', */
    /*     'label' => 'Meeting Date', */
    /*     'weight' => '-4', */
    /*     'description' => '', */
    /*     'type' => 'date_text_repeat', */
    /*     'module' => 'date', */
    /*   ), */
    /* ); */


    # $this->field_name = "meeting_date";
    $this->field = array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_date',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'date',
      'settings' => array(
        'cache_count' => '4',
        'cache_enabled' => 0,
        'granularity' => array(
          'day' => 'day',
          'hour' => 'hour',
          'minute' => 'minute',
          'month' => 'month',
          'second' => 0,
          'year' => 'year',
        ),
        'timezone_db' => 'UTC',
        'todate' => 'optional',
        'tz_handling' => 'site',
      ),
      'translatable' => '0',
      'type' => 'datetime',
    );

    $this->field = field_create_field($this->field);
    $this->field_id = $this->field['id'];
    $this->instance = array(
      'bundle' => 'event',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'date',
          'settings' => array(
            'format_type' => 'long',
            'fromto' => 'both',
            'multiple_from' => '',
            'multiple_number' => '',
            'multiple_to' => '',
          ),
          'type' => 'date_default',
          'weight' => '0',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),  'entity_type' => 'node',
      'field_name' => 'field_date',
      'label' => 'Date',
      'required' => 0,
      'settings' => array(
        'default_value' => 'now',
        'default_value2' => 'strtotime',
        'default_value_code' => '',
        'default_value_code2' => '+2 hours',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'date',
        'settings' => array(
          'display_all_day' => 0,
          'increment' => 15,
          'input_format' => 'Y-m-d H:i:s',
          'input_format_custom' => '',
          'label_position' => 'above',
          'text_parts' => array(),
          'year_range' => '-3:+3',
        ),
        'type' => 'date_text',
        'weight' => '1',
      ),
    );
    field_create_instance($this->instance);
  }

  public function assertLinkLabel($label, $index = 0, $message = '', $group = 'Other') {
    $links = $this->xpath('//a[@label="' . $label . '"]');
    $message = ($message ?  $message : t('Link with label "!label" found.', array('!label' => $label)));
    return $this->assert(isset($links[$index]), $message, $group);
  }

  /**
   *  These are utility functions for the subclasses to use
   */

  public function CreateEvent($options) {
    $this->drupalGet('node/add/event');
    if (array_key_exists('date', $options)) {
      $options['field_date[und][0][value][date]'] = $options['date'];
      unset($options['date']);
    }
    if (array_key_exists('date_to', $options)) {
      $options['field_date[und][0][value2][date]'] = $options['date_to'];
      unset($options['date_to']);
    }

    $this->drupalPost(NULL, $options, t('Save'));
  }

  public function CreateAnnounce($options) {
    $this->drupalGet('admin/config/system/node_announce/add');
    $this->drupalPost(NULL, $options, t('Create'));
  }

  public function Get($url)
  {
    return $this->drupalGet($url);
  }

  public function Post($one, $two, $three)
  {
    return $this->drupalPost($one, $two, $three);
  }

   /**
   * Runs cron in the Drupal installed by Simpletest.
   */
  protected function cronRun() {
    $this->drupalGet($GLOBALS['base_url'] . '/cron.php', array('external' => TRUE, 'query' => array('cron_key' => variable_get('cron_key', 'drupal'))));
  }

}