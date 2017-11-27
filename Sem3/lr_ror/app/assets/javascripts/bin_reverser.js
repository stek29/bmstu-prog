// = require jquery3

$(document).ready(function() {
    var result_div = $('#result');
    result_div.show();

    var render_to = {
        'm_int': result_div.find('#m'),
        'm_bin': result_div.find('#m_bin'),
        'n_int': result_div.find('#n'),
        'n_bin': result_div.find('#n_bin')
    };

    var form = $('#m_form');
    var status = $('#status');
    var hide_these = $('.hide-on-fail');

    hide_these.hide();
    status.text('Enter Number and press Submit');

    form.on('ajax:send', function() {
        status.text('Loading');
        hide_these.hide();
    });

    form.on('ajax:success', function(event) {
        console.log(event);

        var data = event.detail[0];

        render_to.m_int.text(data.num_m.int);
        render_to.m_bin.text(data.num_m.bin_str);
        render_to.n_int.text(data.num_n.int);
        render_to.n_bin.text(data.num_n.bin_str);

        status.text('Result:');
        hide_these.show();
    });

    form.on('ajax:error', function() {
        console.log(event);
        status.text('Error!');
    })
});
