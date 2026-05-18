
let cards = document.querySelectorAll('.card');


cards.forEach(card => {
    card.addEventListener('dblclick', () => {
        double_c(card);
    });
});

function double_c(c){
    c.classList.toggle('dark-bold-card');
}


function clear_actions(){

    let dbc = document.querySelectorAll('.dark-bold-card');
    dbc.forEach(c =>{
        c.classList.toggle('dark-bold-card');
    } );

    show_cards();


}


document.querySelector('#shw_g').addEventListener('mouseenter', ghost_cards);
document.querySelector('#shw_g').addEventListener('mouseleave', hide_ghosts);


let cols = document.querySelectorAll('.col');


function show_cards() {
   
    cols.forEach(co => {
        co.style.display = '';
         
    }); 
}



function ghost_cards() {
    cols.forEach(co => {
        if (co.style.display === 'none' ) {
            co.style.display = ''; 
            co.style.opacity = '0.3'; 
            co.style.pointerEvents = 'none'; 
        }
        
    }); 
}

function hide_ghosts() {
    cols.forEach(co => {
        if (co.style.opacity === '0.3') {
            co.style.display = 'none'; 
            co.style.opacity = '';      
            co.style.pointerEvents = ''; 
        }
    });
}