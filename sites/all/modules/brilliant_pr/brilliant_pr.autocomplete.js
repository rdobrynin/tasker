(function ($) {
    Drupal.jsAC.prototype.populatePopup = function () {
        var $input = $(this.input);
        var position = $input.position();
        // Show popup.
        if (this.popup) {
            $(this.popup).remove();
        }
        this.selected = false;
        this.popup = $('<div id="autocomplete"></div>')[0];
        this.popup.owner = this;
        $(this.popup).css({
            top: parseInt(position.top + this.input.offsetHeight, 10) + 'px',
            left: parseInt(position.left, 10) + 'px',
            width: $input.innerWidth() + 'px',
            display: 'none'
        });
        $input.before(this.popup);

        // Do search.
        this.db.owner = this;
        if ($(this.input).attr('custom-autocomplete') == 'autocomplete') {
            this.db.customSearch(this.input.value);
        } else {
            this.db.search(this.input.value);
        }

    };


    Drupal.ACDB.prototype.customSearch = function (searchString) {
        // loop through all elements with the filter attribute and add them to the string
        $.each($("[custom-autocomplete=filter]"), function(i,v) {
            var element = $(v);
            searchString = element.val() + "/" + searchString;
        });

        return this.search(searchString);
    };

})(jQuery);