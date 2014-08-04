<?php

/**
 * @file
 * Template for Back to Parent link.
 * Variables:
 *   $btp_link_item
 *     contains the parent menu item array, and block config settings.
 *   $btp_prefix
 *     contains the prefix string.
 *   $btp_suffix
 *     contains the suffix string.
 */

?>
<?php if (isset($btp_link_item)) : ?>
<div class="btp-link">
  <?php print l($btp_link_item['btp_prefix'] . $btp_link_item['link_title'] . $btp_link_item['btp_suffix'], $btp_link_item['link_path'], $btp_link_item['localized_options']);?>
</div>
<?php endif; ?>
