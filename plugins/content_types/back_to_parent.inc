<?php
$plugin = array(
  'single' => TRUE,  // Just do this one, it is needed.
  'title' => t('Back to parent'),  // Title to show up on the pane screen.
  'description' => t('Back to parent menu item link'), // Description to show up on the pane screen.
  'edit form' => 'a10_careers_iframe_pane_custom_pane_edit_form', // A function that will return the settings form for the pane.
  'render callback' => 'a10_careers_iframe_pane_custom_pane_render', // A function that will return the renderable content.
  'admin info' => 'a10_careers_iframe_pane_custom_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
);

/**
 * Run-time rendering of the body of the block (content type)
 */
function a10_careers_iframe_pane_custom_pane_render($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->module = 'back_to_parent';
  $block->title = '';

  $parent_item = back_to_parent_plid()
  if (!empty($plid_item)) {
    $parent_item_link = l($plid_item['title'], $plid_item['href'], array('attributes' => array('class' => 'back-to-link')));
  }
  $content = array(
    '#attributes' => array('class' => array('back-to-parent-link')),
    '#markup' => $parent_item_link,
  );
  $block->content = $content;

  return $block;
}