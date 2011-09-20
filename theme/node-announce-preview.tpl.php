<?php
  /**
   * @file
   * Template to display the current lendee of an item.  This template is only
   * ever reached if there is a valid checkout for an item, otherwise we never
   * get here, so assume $user and $reservation are filled out.
   *
   * $queue - the request queue
   * $node - the node in question
   * $user - the current user, so we can see if they've got requests
   *
   */
?>
<div class="node-announce-preview">

  <pre><?php print var_export(content_fields('field_meeting_date', 'meeting'), true); ?></pre>
  <div id="node-announce-preview-from">From: <?php print $announce->email_from; ?></div>
  <div id="node-announce-preview-to">To: <?php print $announce->email_to; ?></div>
  <div id="node-announce-preview-subject">Subject: <?php print token_replace($announce->subject, 'node', $node); ?></div>
<div id="node-announce-preview-body"><?php print token_replace($announce->message, 'node', $node); ?></div>
</div>
