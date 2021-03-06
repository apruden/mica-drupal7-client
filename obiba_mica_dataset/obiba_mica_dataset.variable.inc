<?php

/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * Implements hook_variable_info().
 */

function obiba_mica_dataset_variable_info($options) {
  _obiba_mica_dataset_variable_content($variable);
  _obiba_mica_dataset_variable_variable_content($variable);
  return $variable;
}

/**
 * Setting Variable content page.
 */
function _obiba_mica_dataset_variable_content(&$variable) {
  $variable['dataset_detailed_crosstab'] = array(
    'title' => t('Show the Crosstab Button'),
    'description' => t('If selected, the Crosstab Button will be displayed.'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['dataset_title_acronym_setup'] = array(
    'title' => t('Show acronym on the title'),
    'description' => t('If selected, the acronym is shown in the title page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['dataset_show_studies'] = array(
    'title' => t('Show studies'),
    'description' => t('If selected the Studies section will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['dataset_list_show_search_button'] = array(
    'title' => t('Show the search datasets button in the dataset list page'),
    'description' => t('If selected the search datasets button will be displayed in the dataset list page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['dataset_detail_show_search_button'] = array(
    'title' => t('Show the search variables button in the dataset page'),
    'description' => t('If selected the search variables button will be displayed in the dataset page'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['dataset_description_overview_field'] = array(
    'title' => t('Show description inside overview'),
    'description' => t('If selected, dataset description is shown as a plain text inside the overview section.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['dataset_harmonization_impossible_icon'] = array(
    'title' => t("Icon to show for the 'Impossible' status"),
    'description' => t("Select,the Icon to show for 'Impossible' harmonization status"),
    'type' => 'string',
    'default' => ObibaDatasetConstants::IMPOSSIBLE_HARMO_ICON,
  );
  $variable['dataset_harmonization_impossible_label'] = array(
    'title' => t("Label to show for the 'Impossible' status"),
    'description' => t("Text to display, for the label to show for 'Impossible' harmonization status"),
    'type' => 'string',
    'default' => t('Impossible'),
  );
  $variable['dataset_harmonization_undetermined_icon'] = array(
    'title' => t("Icon to show for the 'Undetermined' status"),
    'description' => t("Select,the Icon to show for 'Undetermined' harmonization status"),
    'type' => 'string',
    'default' => ObibaDatasetConstants::UNDETERMINED_HARMO_ICON,
  );
  $variable['dataset_harmonization_undetermined_label'] = array(
    'title' => t("Label to show for the 'Undetermined' status"),
    'description' => t("Text to display, for the label to show for 'Undetermined' harmonization status"),
    'type' => 'string',
    'default' => t('Undetermined'),
  );
}
/**
 * Setting Variable content page.
 */
function _obiba_mica_dataset_variable_variable_content(&$variable) {
  $variable['variable_show_studies'] = array(
    'title' => t('Show studies'),
    'description' => t('If selected the Studies section will be displayed'),
    'type' => 'string',
    'default' => TRUE,
  );
  $variable['variable_show_networks'] = array(
    'title' => t('Show networks'),
    'description' => t('If selected the Networks section will be displayed'),
    'type' => 'string',
    'default' => TRUE,
  );
  $variable['dataset_detailed_var_stats'] = array(
    'title' => t('Show detailed harmonization variable data statistics'),
    'description' => t('If selected, detailed data summary and crosstab statistics about each harmonized variables will be displayed when querying the harmonization variable data statistics.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['mica_statistics'] = array(
    'title' => t('Show data statistics'),
    'description' => t('If selected, variable pages will include a statistics summary section and a link to the crosstab page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['variable_algorithm'] = array(
    'title' => t('Show harmonization algorithms'),
    'description' => t('If selected, the harmonization algorithms will be displayed in the harmonization dataset and in the harmonized variable pages.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
}
