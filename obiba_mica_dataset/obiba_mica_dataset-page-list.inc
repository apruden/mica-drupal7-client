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
 * @file
 * Code to dataset list page.
 */

include_once 'includes/obiba_mica_dataset_resource.inc';

/**
 * Get the dataset list.
 */
function obiba_mica_dataset_get_datasets_list() {
  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('dataset_page'));
  drupal_set_title($node_rendered['#node']->title);
  return obiba_mica_dataset_get_datasets_page($node_rendered, 'datasets');
}

/**
 * Get the harmonized dataset list.
 */
function obiba_mica_dataset_get_harmonization_datasets_list() {
  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('harmo_dataset_page'));
  drupal_set_title($node_rendered['#node']->title);
  return obiba_mica_dataset_get_datasets_page($node_rendered, 'harmonization_datasets');
}

/**
 * Get the study dataset list.
 */
function obiba_mica_dataset_get_study_datasets_list() {
  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('study_dataset_page'));
  drupal_set_title($node_rendered['#node']->title);
  return obiba_mica_dataset_get_datasets_page($node_rendered, 'study_datasets');
}

/**
 * Render the dataset list on a page template.
 */
function obiba_mica_dataset_get_datasets_page($node_view, $dataset_resource) {
  $context['url'] = '/drupal/mica/refresh_list_datasets_' . $dataset_resource;
  drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');
  $query = NULL;
  $sort = NULL;
  $sort_by = NULL;
  $list_datasets = '';
  $dataset_limits = NULL;
  if (!empty($_GET['search-query'])) {
    $query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $sort_by = $_GET['search-sort-order'];
  }
  if (!empty($_GET['search-nbr-result'])) {
    $dataset_limits = $_GET['search-nbr-result'];
  }
  $node_view['#node']->title = '';
  $resource_dataset = obiba_mica_dataset_correct_resource_server($dataset_resource);
  $response = obiba_mica_dataset_get_datasets($query, $sort, $sort_by, $resource_dataset, $dataset_limits);
  $total_hits = empty($response) ? 0 : $response->getTotalHits();
  $dataset_limits = !empty($dataset_limits) ? $dataset_limits : MicaClient::getResponsePageSizeSmall();
  pager_default_initialize($total_hits, $dataset_limits);
  $pager_output = theme('pager', array('quantity' => $dataset_limits));
  $summaries = empty($response) ? array() : $response->getSummaries();
  if (!empty($summaries)) {
    foreach ($summaries as $dataset) {
      $list_datasets .= theme('obiba_mica_dataset-list-page-block', array(
        'dataset' => $dataset,
      ));
    }
  }
  else {
    $list_datasets = variable_get_value('datasets_empty_label');
  }
  return theme('obiba_mica_dataset-list', array(
    "form_search" => drupal_get_form('obiba_mica_dataset_create_form'),
    'node_page' => $node_view,
    "total_items" => $total_hits,
    'list_datasets' => $list_datasets,
    'pager_wrap' => $pager_output,
    'dataset_type' => $dataset_resource,
  ));
}

/**
 * Helper to parse the correct resource mica server.
 */
function obiba_mica_dataset_correct_resource_server($dataset_resource) {
  $resource = array(
    'datasets' => NULL,
    'harmonization_datasets' => 'HarmonizationDataset',
    'study_datasets' => 'StudyDataset',
  );
  return $resource[$dataset_resource];
}

/**
 * Get the datasets from server.
 */
function obiba_mica_dataset_get_datasets($query, $sort, $sort_by, $dataset_resource, $dataset_limits = NULL) {
  $from = 0;
  $resource = new MicaDatasetResource();
  $size_response = !empty($dataset_limits) ? $dataset_limits : variable_get_value('mica_response_page_size_small');
  if (!empty($_GET['page'])) {
    $from = $resource->paginationListSearchParameters($_GET['page'], 'datasets', $size_response);
  }
  $response = $resource->getDatasets($dataset_resource, NULL, $query, $from, $size_response, $sort, $sort_by);
  if (!empty($response)) {
    $_SESSION['datasets']['aggregations']['total_hits'] = $response->getTotalHits();
  }

  return $response;
}

/**
 * Search form creation on the dataset list page.
 */
function obiba_mica_dataset_create_form() {
  $context = array(
    'options' => array(),
  );
  return obiba_mica_commons_create_search_form($context);
}

/**
 * Ajax callback to retrieve datasets.
 */
function obiba_mica_dataset_retrieve_datasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = obiba_mica_dataset_get_datasets($query, $sort, $sort_order, NULL);
  drupal_json_output(obiba_mica_dataset_themed_list_dataset($list_datasets));
}

/**
 * Ajax callback to retrieve harmonized datasets.
 */
function obiba_mica_dataset_retrieve_harmonizationDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = obiba_mica_dataset_get_datasets($query, $sort, $sort_order, 'HarmonizationDataset');
  drupal_json_output(obiba_mica_dataset_themed_list_dataset($list_datasets));
}

/**
 * Ajax callback to retrieve study datasets.
 */
function obiba_mica_dataset_retrieve_studyDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = obiba_mica_dataset_get_datasets($query, $sort, $sort_order, 'StudyDataset');
  drupal_json_output(obiba_mica_dataset_themed_list_dataset($list_datasets));
}

/**
 * Theme block datasets list.
 */
Function obiba_mica_dataset_themed_list_dataset($list_datasets) {
  $list_datasets_rendered = '';
  foreach ($list_datasets->getSummaries() as $dataset) {
    $list_datasets_rendered .= theme('obiba_mica_dataset-list-page-block', array(
      'dataset' => $dataset,
    ));
  }
  $data['list'] = $list_datasets_rendered;
  $data['total'] = $list_datasets->getTotalHits();
  return $data;
}

/**
 * GEt datasets table.
 */
function _obiba_mica_dataset_get_datasets_table($datasets, $type) {
  $dataset_rows = array();
  foreach ($datasets as $key_dataset => $dataset_dto) {
    $dce_description = NULL;
    if (!empty($dataset_dto->description)) {
      $dataset_description = theme('box',
        truncate_utf8(strip_tags(obiba_mica_commons_get_localized_field($dataset_dto, 'description')), 50, TRUE, TRUE));
    }
    $dataset_name = obiba_mica_commons_get_localized_field($dataset_dto, 'name');

    $dataset_rows[$key_dataset] = array(
      'data' => array(
        'label' => l($dataset_name, 'mica/' . $type . '/' . $dataset_dto->id),
        'desc' => !empty($dataset_description) ? $dataset_description : '-',
      ),
    );
  }

  $dataset = theme(
    'table',
    array(
      'header' => array(t('Name'), t('Description')),
      'rows' => $dataset_rows,
      'empty' => variable_get_value('datasets_empty_label'),
      'sticky' => FALSE,
      'attributes' => array('id' => 'variables_overview'),
    )
  );
  return $dataset;
}

/**
 * Check the dataset type.
 */
function obiba_mica_dataset_type($dataset) {
  return $dataset->variableType == 'Study' ? 'study-dataset' : 'harmonization-dataset';
}
