<?php

/**
 * Creates/returns a form to configure the btp variables.
 *
 * @param array $form
 * @param array $form_state
 * @return array
 */
function back_to_parent_settings($form, &$form_state) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->language == 'en') ? '' : ' - ' . $language->native;

  $number_of_btp_blocks = variable_get('btp_number_of_back_to_parent_blocks' . $lang, 1);
  $form['btp_number_of_back_to_parent_blocks' . $lang] = array(
    '#type' => 'select',
    '#title' => t('Number of available blocks') . $lang_name,
    '#default_value' => $number_of_btp_blocks,
    '#options' => drupal_map_assoc(range(1, 10)),
    '#description' => t('This will enable multiple "Back to Parent" link blocks. Each block has its own configurable settings. '),
  );

  $enable_btp_panel_pane = variable_get('btp_enable_panel_pane' . $lang, TRUE);
  $form['btp_enable_panel_pane' . $lang] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable panel pane') . $lang_name,
    '#default_value' => $enable_btp_panel_pane,
    '#description' => t('This will enable a panel pane.'),
  );

  $enable_btp_page_variable = variable_get('btp_enable_page_variable' . $lang, TRUE);
  $form['btp_enable_page_variable' . $lang] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable page.tpl.php variable') . $lang_name,
    '#default_value' => $enable_btp_page_variable,
    '#description' => t('This will enable a <em>\$back_to_parent_link</em> variable for use in your own page.tpl.php.'),
  );

  return system_settings_form($form);
}
