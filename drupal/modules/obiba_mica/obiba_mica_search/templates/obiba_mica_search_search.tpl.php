<?php //dvm('search var',$studies);
?>
<div class="alert alert-info">
  <div id="search-help">
    <i class="glyphicon glyphicon-arrow-left"></i>
    <span class="indent">
      <?php print t('Start searching by selecting a facet'); ?>
    </span>
  </div>
  <div id="search-query"></div>
</div>

<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">
    <li><a href="#networks" role="tab"> <?php print t('Networks') ?>
        (<?php print !empty($network_total_hits) ? $network_total_hits : 0; ?>)
      </a>
    </li>

    <li><a href="#studies" role="tab"> <?php print t('Studies') ?>
        (<?php print !empty($study_total_hits) ? $study_total_hits : 0; ?>)
      </a>
    </li>

    <li><a href="#datasets" role="tab"> <?php print t('Datasets') ?>
        (<?php print !empty($dataset_total_hits) ? $dataset_total_hits : 0; ?>)
      </a>
    </li>

    <li class="active"><a href="#variables" role="tab"><?php print t('Variables') ?>
        (<?php print !empty($variable_total_hits) ? $variable_total_hits : 0; ?>)
      </a>
    </li>

  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">
    <div class="tab-pane active" id="variables">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Variables') ?></h3>

          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($variable_search_form) ?>
            <p>
              <?php print l(t('View Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query,
                  'group-by' => 'studyIds'
                ),
              )); ?>
            </p>
          </div>
          <div class="clearfix"/>
          <?php print $variables_result['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="datasets">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Datasets') ?></h3>

          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($dataset_search_form) ?>
            <p>
              <?php print l(t('View Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query,
                  'group-by' => 'datasetId'
                ),
              )); ?>
            </p>
          </div>

          <div class="clearfix"/>
          <?php print $datasets['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="studies">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Studies') ?></h3>

          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($study_search_form) ?>
            <p>
              <?php print l(t('View Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query,
                  'group-by' => 'studyIds'
                ),
              )); ?>
            </p>
          </div>
          <div class="clearfix"/>
          <?php print $studies['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="networks">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Networks') ?></h3>

          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($network_search_form) ?>
            <p>
              <?php print l(t('View Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query,
                  'group-by' => 'studyIds'
                ),
              )); ?>
            </p>
          </div>
          <div class="clearfix"/>
          <?php print $networks['data']; ?>
        </section>
      </article>
    </div>

  </div>
</div>