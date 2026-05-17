

document.addEventListener("DOMContentLoaded", function () {
    document.getElementById("contentFrame").src = "home.html";
  
});



function navigatePage(btnSelected, url ) {
    //1)  )get all buttons that are in the menu
    // that have class of menu-btn
    const buttons =
        document.querySelectorAll(".menu-btn");
    // run on all the buttons 
    buttons.forEach(btn => {
        //2) remove the selected for eatch
        btn.classList.remove("selected");
    });
    
    // 3) set selected on the spesific button the function recived 
    btnSelected.classList.add("selected");
    // 4) change the sorce url to the one the button 

    // getElementById is kinda equall to -> querySelector("#contentFrame")
    // it changes the html sorce DOES NOT CHANE TO A NEW PAGE!!!!
    document.getElementById("contentFrame").src = url;

   
}

