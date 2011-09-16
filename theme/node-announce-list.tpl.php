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
<div class="node-announce-list">
  <table><tr><th>From</th><th>To</th><th>Type</th><th>Subject</th><th>Days Before</th></tr>
  <?php foreach($announces as $item): ?>
  <tr>
    <td><?php print $item->email_from; ?></td>
    <td><?php print $item->email_to; ?></td>
    <td><?php print $item->date_field; ?></td>
    <td><?php print $item->subject; ?></td>
    <td><?php print $item->schedule; ?></td>
  </tr>
  <?php endforeach; ?>
  </table>
</div>
