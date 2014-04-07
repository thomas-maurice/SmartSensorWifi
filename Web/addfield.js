// Javascript used to add dynamically new submit field

var div = document.getElementById('champs');

// Create the new field
function addInput(name,placeholder){
    var input = document.createElement("input");
    input.name = name;
    input.placeholder = placeholder; 
    div.appendChild(input);
}

// Add the field to the page
function addField() {
	div.appendChild(document.createElement("br"));
	addInput("name[]","Nom du capteur");
	addInput("password[]","Mot de passe du capteur");
}

// Add the field (for deletion page)
function delField() {
	div.appendChild(document.createElement("br"));
	addInput("name[]","ID du capteur");
}