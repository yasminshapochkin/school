

let cards = document.querySelectorAll('.card');

let cols = document.querySelectorAll('.col');



function show_cards() {
   
    cols.forEach(co => {
        co.style.display = '';
         
    }); 
    cards.forEach(card => {
        card.style.display = '';
         
    }); 

}



cards.forEach(card => {
    card.addEventListener('dblclick', () => {
        double_c(card);
    });
});

function double_c(c){
    c.classList.toggle('selected-card');
}


function clear_actions(){

    let dbc = document.querySelectorAll('.selected-card');
    dbc.forEach(c =>{
        c.classList.toggle('selected-card');
    } );

    


}


document.querySelector('#shw_g').addEventListener('mouseenter', ghost_cards);
document.querySelector('#shw_g').addEventListener('mouseleave', hide_ghosts);



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

function show_selected(){
    cards.forEach(card=>{
        if (!card.classList.contains("selected-card") && card.style.display === "") {
            card.style.display = "none";
        }

    }

    );


}