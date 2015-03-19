/**
 * @file
 * JScript code for dealing with collapsible blocks
 */

(function ($) {
  Drupal.behaviors.obiba_mica_facet_search_collapse_block = {
    attach: function (context, settings) {
      if (context === document) {
        collapseAllFirstTime();
        if (settings.expand_strategy && settings.expand_strategy === 'expand_groups') {
          expandGroups();
        }

        updateExpandCollapseIconParent();
        setupDomEventHandlers();
        return;
      }

      /********** Show more show less on search page********/
      $('.charts', context).on('shown.bs.collapse', function () {
        $('.text-button-field').html(Drupal.t('Show less'));
      });

      $('.charts', context).on('hidden.bs.collapse', function () {
        $('.text-button-field').html(Drupal.t('Show all'));
      });

      /********* More/Less in search block ********/
      $(".expand-control").each(function () {
        var controlSelector = '.expand-control-div-' + $(this).attr('id');
        var linkSelector = '.expand-control-link-' + $(this).attr('id');

        $(controlSelector).on('shown.bs.collapse', function () {
          $(linkSelector).html(Drupal.t('Less'));
        });

        $(controlSelector).on('hidden.bs.collapse', function () {
          $(linkSelector).html(Drupal.t('More'));
        });
      });

      /**
       * When there is only one taxomomy group and no other facet filters, place the icon inside the group
       */
      function updateExpandCollapseIconParent() {
        if ($('#search-facets .tab-pane.active #collapsible-taxonomy').length === 1
          && $('#search-facets .tab-pane.active>section>.block-content').length === 0) {
          $("a#collapsible-taxonomy").parent().append($("#facets-expand-collapse").addClass("pull-right").detach());
        }
      }

      function setupDomEventHandlers() {
        $('#facets-expand-collapse', context).on('click', function (e) {
          e.preventDefault();
          $(this).blur();

          if($(this).data('allCollapsed')) {
            expandAll();
          } else {
            collapseAll();
          }

          updateExpandCollapseIcon();
        });

        $('.block', context).on('shown.bs.collapse', function () {
          updateExpandCollapseIcon();
        });

        $('.block', context).on('hidden.bs.collapse', function () {
          updateExpandCollapseIcon();
        });
      }

      function updateExpandCollapseIcon(firsttime) {
        var allCollapsed = true;

        $('#search-facets .tab-pane.active #collapsible-taxonomy').each(function () {
          allCollapsed &= $(this).hasClass('collapsed');
        });

        $('#search-facets .tab-pane.active>section>.block-content').each(function () {
          if ($(this).find('form.autocomplete').length && firsttime) {
            return;
          }

          allCollapsed &= ($(this).hasClass('collapse') || $(this).hasClass('collapsing'));
        });

        $("#facets-expand-collapse").data('allCollapsed', allCollapsed).text(allCollapsed ? "[+]" : "[-]");
      }

      function expandAll() {
        expandGroups();

        $(".block-content").each(function (id, state) {
          var current_id = this.id;
          if (!current_id || current_id === "collapse-block-obiba-mica-search-facet-search") return true;
          $("#" + current_id).collapse("show");
          removeCollapsedIcon(current_id, "collapsed");
        });

        updateExpandCollapseIcon();
      }

      function collapseAllFirstTime() {
        collapseAllInternal(true);
      }

      function collapseAll() {
        collapseAllInternal(false);
      }

      function collapseAllInternal(firstTime) {
        collapseGroups();

        $(".block-content").each(function (id, state) {
          var current_id = this.id;

          if (!current_id || current_id === "collapse-block-obiba-mica-search-facet-search") {
            return true;
          }

          if (firstTime && $("form[class='autocomplete']", $("#" + current_id)).length > 0) {
            $("#" + current_id).collapse("show");
            return true;
          }

          $("#" + current_id).collapse("hide");
          addCollapsedIcon(current_id, 'collapsed');
        });

        updateExpandCollapseIcon(firstTime);
      }

      function expandGroups() {
        var taxonomies = $("div[id^='taxonomy-']");
        taxonomies.collapse('show');
        if (taxonomies.length === 1) {
          $("a#collapsible-taxonomy").removeClass("accordion-toggle").attr("data-toggle", null).attr("href", null);
        }
        $("a#collapsible-taxonomy").removeClass('collapsed');
      }

      function collapseGroups() {
        $("div[id^='taxonomy-']").collapse('hide');
        $("a#collapsible-taxonomy").addClass('collapsed');
      }

      function removeCollapsedIcon(current_id, collapse) {
        if (collapse && current_id) {
          sectionid = current_id.replace("collapse-", "");
          $("a[data-parent=" + sectionid + "]").removeClass(collapse);
        }
      }

      function addCollapsedIcon(current_id, collapse) {
        if (collapse && current_id) {
          sectionid = current_id.replace("collapse-", "");
          $("a[data-parent=" + sectionid + "]").addClass(collapse);
        }
      }
    }
  }
}(jQuery));
