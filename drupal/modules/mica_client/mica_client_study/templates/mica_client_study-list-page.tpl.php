<?php //dpm($studies->studySummaries); ?>
<?php print render($node_page) ?>
<?php //dpm($studies); ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php if ($studies->total > 0): ?>
        <?php print $studies->total . ' ' . ($studies->total == 1 ? t('Study') : t('Studies')); ?>
      <?php else: print t('No studies found'); ?>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <?php print render($form_search); ?>
    </div>
  </div>

  <?php if (!empty($studies->studySummaries)): ?>
    <?php foreach ($studies->studySummaries as $study) : ?>
      <div class="row lg-bottom-margin">
        <div class="col-md-2 col-xs-2">
          <?php if (!empty($study->logo)): ?>
            <img typeof="foaf:Image"
                 src="http://localhost:8082/ws/draft/study/<?php print $study->id ?>/file/<?php print $study->logo->id ?>/_download"
                 width="120" height="96" alt="">
          <?php else : ?>
            <h1 class="big-character">
              <span class="t_badge color_S"><?php print t('S') ?></span>
            </h1>
          <?php endif; ?>
        </div>
        <div class="col-md-10 col-xs-10">
          <h4><a
              href="study/<?php print $study->id ?>">
              <?php print mica_client_commons_get_localized_field($study, 'acronym') . ' - ' . mica_client_commons_get_localized_field($study, 'name'); ?>
            </a>
          </h4>

          <p>
            <?php print truncate_utf8(mica_client_commons_get_localized_field($study, 'objectives'), 300, TRUE, TRUE); ?>
          </p>
        </div>
      </div>

    <?php endforeach; ?>
    <div><?php print $pager_wrap; ?></div>
  <?php endif; ?>
</div>
