<?php

/**
 * Creates/returns a form to configure the btp variables.
 *
 * @param array $form
 * @param array $form_state
 * @return array
 */
function back_to_parent_settings($form, &$form_state) {
  $number_of_btp_blocks = variable_get('btp_number_of_back_to_parent_blocks', 1);
  $form['btp_number_of_back_to_parent_blocks'] = array(
    '#type' => 'select',
    '#title' => t('Number of available blocks'),
    '#default_value' => $number_of_btp_blocks,
    '#options' => drupal_map_assoc(range(1, 10)),
    '#description' => t('This will enable multiple "Back to Parent" link blocks. Each block has its own configurable settings. '),
  );

  $enable_btp_panel_pane = variable_get('btp_enable_panel_pane', TRUE);
  $form['btp_enable_panel_pane'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable panel pane'),
    '#default_value' => $enable_btp_panel_pane,
    '#description' => t('This will enable a panel pane.'),
  );

  $enable_btp_page_variable = variable_get('btp_enable_page_variable', TRUE);
  $form['btp_enable_page_variable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable page.tpl.php variable'),
    '#default_value' => $enable_btp_page_variable,
    '#description' => t('This will enable a <em>\$back_to_parent_link</em> variable for use in your own page.tpl.php.'),
  );

  return system_settings_form($form);
}
