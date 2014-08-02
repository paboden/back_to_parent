<?php
$plugin = array(
  'single' => TRUE,  // Just do this one, it is needed.
  'title' => t('Back to parent'),  // Title to show up on the pane screen.
  'description' => t('Back to parent menu item link'), // Description to show up on the pane screen.
  'category' => 'Widgets', // Category to place this pane in.
  'edit form' => 'back_to_parent_pane_edit_form', // A function that will return the settings form for the pane.
  'render callback' => 'back_to_parent_pane_render', // A function that will return the renderable content.
  'admin info' => 'back_to_parent_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
);

/**
 * Set the Back to parent pane admin info.
 */
function back_to_parent_pane_admin_info($subtype, $conf, $contexts) {
  $block = new stdClass;
  $block->title = (isset($conf['override_title'])) ? $conf['override_title_text'] : t('Back to Parent link');
  $block->content = t('Creating a link back to the parent of this page. Current page must be in a menu for this to be active.');

  return $block;
}

/**
 * Create the Back to parent pane edit form.
 */
function back_to_parent_pane_edit_form($form, $form_state) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->name == 'en') ? '' : ' - ' . $language->name;

  $conf = $form_state['conf'];

  $form['btp_pane_prefix' . $lang] = array(
    '#type' => 'textfield',
    '#title' => t('Link Prefix'),
    '#default_value' => $conf['btp_pane_prefix' . $lang],
  );
  // Suffix to display after the parent item link
  $form['btp_pane_suffix' . $lang] = array(
    '#type' => 'textfield',
    '#title' => t('Link Suffix') . $lang_name,
    '#default_value' => $conf['btp_pane_suffix' . $lang],
  );

  return $form;
}

/**
 * Save the Back to parent pane edit form.
 */
function back_to_parent_pane_edit_form_submit($form, $form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }

  return $form;
}

/**
 * Run-time rendering of the back to parent pane (content type)
 */
function back_to_parent_pane_render($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->module = 'back_to_parent';
  $block->title = '';

  $parent_item = back_to_parent_item();
  if (!empty($parent_item)) {
    $parent_item_link = l($parent_item['title'], $parent_item['href'], array('attributes' => array('class' => 'back-to-link')));
  }
  $content = array(
    '#attributes' => array('class' => array('back-to-parent-link')),
    '#markup' => $parent_item_link,
  );
  $block->content = $content;

  return $block;
}