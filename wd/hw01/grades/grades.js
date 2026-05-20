
document.addEventListener('DOMContentLoaded', function () {

    let cards = document.querySelectorAll('.card');

    let shw_sl = document.querySelector('#shw_sl');
    let shw_al = document.querySelector('#shw_al');
    let clr = document.querySelector('#clr');
    let cols = document.querySelectorAll('.col');
    
    
    shw_al.addEventListener('click', function () {
        cols.forEach(co => { co.style.display = ''; });
        cards.forEach(card => { card.style.display = ''; });

    });

    cards.forEach(card => {
        card.addEventListener('dblclick', () => {
            card.classList.toggle('selected-card');
        });
    });

    shw_sl.addEventListener('click', function () {
        cards.forEach(card => {
            if (!card.classList.contains("selected-card") && card.style.display === "") {
                card.style.display = "none";
            }

        }

        );



    });

    clr.addEventListener('click' , function(){
    let dbc = document.querySelectorAll('.selected-card');


        dbc.forEach(c => {
        c.classList.toggle('selected-card');
    });

    });


});



