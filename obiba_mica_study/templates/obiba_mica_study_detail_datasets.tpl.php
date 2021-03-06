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

?>

<h2><?php print t('Datasets'); ?></h2>
<div id="datasetsDisplay" class="scroll-content-tab" data-dce-variables='<?php print json_encode($datasets['dce_variables']) ?>'
  data-total-variables='<?php print json_encode($datasets['total_variable_nbr']) ?>'>
  <?php print render($datasets['dataset-tab']); ?>
</div>