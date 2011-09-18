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
  <table><tr><th>Name</th><th>Days Before</th><th>Subject</th></tr>
  <?php foreach($announces as $item): ?>
  <tr>
    <td><?php print $item->name; ?></td>
    <td><?php print $item->days_before; ?></td>
    <td><?php print $item->subject; ?></td>
    <td><?php print l('Preview', 'admin/settings/node_announce/' . $item->id . '/preview'); ?></td>
    <td><?php print l('Edit', 'admin/settings/node_announce/' . $item->id . '/edit'); ?></td>
  </tr>
  <?php endforeach; ?>
  </table>
</div>
