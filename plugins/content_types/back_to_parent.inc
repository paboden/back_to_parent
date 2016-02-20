<?php
global $language;
$lang = ($language->language == 'en') ? '' : '_' . $language->language;
$lang_name = ($language->language == 'en') ? '' : ' - ' . $language->name;

$plugin = array(
  'single' => TRUE,  // Just do this one, it is needed.
  'title' => t('Back to Parent'),  // Title to show up on the pane screen.
  'description' => t('Back to parent menu item link'), // Description to show up on the pane screen.
  'category' => 'Widgets', // Category to place this pane in.
  'edit form' => 'back_to_parent_pane_edit_form', // A function that will return the settings form for the pane.
  'render callback' => 'back_to_parent_pane_render', // A function that will return the renderable content.
  'admin info' => 'back_to_parent_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
  'defaults' => array(
    'btp_pane_prefix' . $lang => '',
    'btp_pane_suffix' . $lang => '',
    'btp_pane_view_mode' . $lang => '',
    'btp_pane_view_display' . $lang => '',
  )
);

/**
 * Set the Back to parent pane admin info.
 */
function back_to_parent_pane_admin_info($subtype, $conf, $contexts) {
  $block = new stdClass;
  $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
  $block->content = t('Creating a link back to the parent of this page. Current page must be in a menu for this to be active.');

  return $block;
}

/**
 * Create the Back to parent pane edit form.
 */
function back_to_parent_pane_edit_form($form, $form_state) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->language == 'en') ? '' : ' - ' . $language->name;

  $conf = $form_state['conf'];

  $form['btp_pane_prefix' . $lang] = array(
    '#type' => 'textfield',
    '#title' => t('Link Prefix'),
    '#default_value' => $conf['btp_pane_prefix' . $lang] ? $conf['btp_pane_prefix' . $lang] : '',
  );
  // Suffix to display after the parent item link
  $form['btp_pane_suffix' . $lang] = array(
    '#type' => 'textfield',
    '#title' => t('Link Suffix') . $lang_name,
    '#default_value' => $conf['btp_pane_suffix' . $lang] ? $conf['btp_pane_suffix' . $lang] : '',
  );

  // Get a list of all view modes, plus a view additional styles
  $displays = array(
    'title_as_link' => array(
      'label' => t('Title as link'),
      'custom settings' => FALSE,
    ),
    'title_no_link' => array(
      'label' => t('Title, no link'),
      'custom settings' => FALSE,
    ),
    'separate' => array(
      'label' => t('Separate title and link'),
      'custom settings' => FALSE,
    ),
  );
  $entity_info = entity_get_info('node');
  $view_modes = $entity_info['view modes'];
  $displays = array_merge($displays, $view_modes);
  foreach($displays as $name => $label) {
    $displays[$name] = $label['label'];
  }

  $form['btp_pane_view_mode' . $lang] = array(
    '#type' => 'select',
    '#title' => t('Display type'),
    '#options' => $displays,
    '#default_value' => $conf['btp_pane_view_mode' . $lang] ? $conf['btp_pane_view_mode' . $lang] : NULL,
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
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->language == 'en') ? '' : ' - ' . $language->name;

  $block = new stdClass();
  $block->module = 'back_to_parent';
  $block->title = '';

  $view_mode = (isset($conf['btp_pane_view_mode' . $lang])) ? $conf['btp_pane_view_mode' . $lang] : 'title_as_link';
  $prefix = (!empty($conf['btp_pane_prefix' . $lang])) ? $conf['btp_pane_prefix' . $lang] . ' ' : '';
  $suffix = (!empty($conf['btp_pane_suffix' . $lang])) ? ' ' . $conf['btp_pane_suffix' . $lang] : '';

  $parent_item = btp_get_parent_link_item();
  if (!empty($parent_item)) {
    $node = btp_get_parent_node_item($parent_item['link_path']);
    if (isset($node) && ($view_mode != 'title_as_link') && ($view_mode != 'title_no_link') && ($view_mode != 'separate')) {
      $parent_item = node_view($node, $view_mode, $langcode = NULL);
      $parent_item = drupal_render($parent_item);
    }
    elseif ($view_mode == 'title_no_link') {
      $parent_item = $prefix . $parent_item['title'] . $suffix . ' no-link';
    }
    elseif ($view_mode == 'separate') {
      $parent_item = t('Title: ') . $parent_item['title'] . '<br/>' . t('URL: ') . l($parent_item['href'], $parent_item['href'], array('attributes' => array('class' => 'back-to-link-separate')));
    }
    else {
      $parent_item = l($prefix . $parent_item['title'] . $suffix, $parent_item['href'], array('attributes' => array('class' => 'back-to-link-else')));
    }
    $block->content = array(
      '#markup' => $parent_item,
    );
  }
  else {
    $block = NULL;
  }

  return $block;
}
