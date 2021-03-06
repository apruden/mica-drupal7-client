/*
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
 * JsScript to initialise dataTables widgets
 */

(function ($) {
  Drupal.behaviors.micaDataset_Datatable_init = {

    invalidate: function (context, parent) {
      if (context === document && $('#table-variables').parents(parent.selector).length > 0) {
        var table = $('#table-variables').dataTable();
        if (table) {
          table.fnAdjustColumnSizing();
        }
      }
    },

    attach: function (context, settings) {
      createDataTable();
    }
  };

  function createDataTable() {
    var divDataTableVar = $('#variables-table');
    var typeDataset = divDataTableVar.attr('type-dataset');
    var idDataset = Drupal.settings.datasetId;
    var headerTable = null;
    if (typeDataset) {
      $.ajax({
        'async': false,
        'url': Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/variables-tab-header/' + typeDataset + '/' + idDataset,
        'type': 'GET',
        'success': function (data) {
          setHeaderTab(data);
        },
        "dataType": "json",
        'error': function (data) {
        }
      });
    }
    function setHeaderTab(data) {
      headerTable = data["header"];
      if (headerTable) {
        $("#download-btn").show();
        var divTableVariable = $('#table-variables');
        divTableVariable.on('xhr.dt', function (e, settings, json) {
          if (json.iTotalRecords === 0) {
            $(".table-variables").hide();
          }
          else {
            $("#download-btn > a").on('click', function (event) {
              // create a form for the file upload
              var form = $("<form action='" + idDataset + '/download' + "' method='post'>");
              $(this).after(form);
              form.submit().remove();
              return false;
            });
          }
        });
        var dataTable = divTableVariable.dataTable({
          "bAutoWidth": false,
          "responsive": true,
          "scrollCollapse": true,
          "processing": true,
          "sDom": '<"table-var-wrapper" <"md-top-margin" i>r<"scroll-content-tab" t><"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
          "bServerSide": true,
          "iDisplayLength": 25,
          "sAjaxSource": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset,
          "aoColumns": headerTable,
          "searching": true,
          "ordering": true,
          "fnDrawCallback": function (oSettings) {
            updateTooltip();
          },
          "fnInitComplete": function () {
            updateTooltip();
          },
          "language": {
            "url": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/datatable-international'
          }
        });

        function updateTooltip() {
          $('span', dataTable.fnGetNodes()).tooltip({
            "delay": 0,
            "track": true,
            "fade": 250
          });
        }
      }
    }

  }

}(jQuery));
