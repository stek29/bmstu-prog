const quantityHTML = `
    <td>
        <button class="hidden" onclick="changeQuantity(this, -1);">-</button>
        <span class="quantity">0</span>
        <button class="hidden" onclick="changeQuantity(this, +1);">+</button>
    </td>
`;

function addProduct() {
    var name = $('#add-name').val();
    var price = $('#add-price').val();


    if (name.length == 0) {
        $('#add-status').html('Некорректное имя');
        return;
    }

    var priceInt = parseInt(price);
    if (! (priceInt > 0)) {
        $('#add-status').html('Некорректная цена');
        return;
    }

    $('#add-status').html('');

    var quantityEl = $(quantityHTML).hover(
        function() {
            $(this).find('button').removeClass('hidden')
        }, function() {
            $(this).find('button').addClass('hidden')
        }
    );

    var el = $(`
    <tr>
        <td class="name">${name}</td>
        <td class="price">${price}</td>
    </tr>
    `)
    .append(quantityEl)
    .appendTo($('#products'));
}

function changeQuantity(btn, by) {
    btn = $(btn);
    var qSpan = btn.parent().find('span.quantity');
    var quantity = parseInt(qSpan.html()) + by;

    if (quantity == -1) {
        btn.parent().parent().remove();
    } else {
        qSpan.html(quantity.toString());
    }
}

function showReciept() {
    var els = [];

    $('#products tr').each(function (_, el) {
        if (_ == 0) return;
        el = $(el);

        els.push([
            el.find('.name').html(), parseInt(el.find('.price').html()), parseInt(el.find('.quantity').html())
        ]);
    });

    var elsJq = els
    .filter(el => el[2]) // remove if quantity == 0
    .map(el => $(`
    <tr>
        <td>${el[0] /*name*/}</td>
        <td>${el[1] * el[2] /*price*quantity*/}</td>
    </tr>
    `));

    $('#reciept')
    .html(`
    <tr>
        <td>Наименование</td>
        <td>Стоимость</td>
    </tr>
    `)
    .append(elsJq);
}