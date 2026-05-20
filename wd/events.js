

let btn1 = document.getElementById("btn1")



btn1.addEventListener("click", function () {
    alert("button clicked!")
  
});

// when page is Loaded in the browser 
// what happends is the DOMdocument event if fired.
document.addEventListener("DOMContentLoaded", function () {
    PageLoaded();
  
});

function PageLoaded(){
    document.getElementById("title").innerHTML = "HTML is loaded!";
    
}

