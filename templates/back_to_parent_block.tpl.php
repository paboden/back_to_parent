<?php

/**
 * @file
 * Template for Back to Parent link.
 * Variables:
 *   $back_to_parent_link
 *     contains the parent menu item array, and block config settings
 */
?>

<?php if (isset($back_to_parent_link)) : ?>
  <?php print l($back_to_parent_link['title'], $back_to_parent_link['href']);?>
<?php endif; ?>
