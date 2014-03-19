var div = document.getElementById('champs');

// Création du champ
function addInput(name,placeholder){
    var input = document.createElement("input");
    input.name = name;
    input.placeholder = placeholder; 
    div.appendChild(input);
}

// Ajout du champ
function addField() {
	div.appendChild(document.createElement("br"));
	addInput("name[]","Identifiant");
}

// Ajout du champ (pour delete)
function delField() {
	div.appendChild(document.createElement("br"));
	addInput("name[]","ID du capteur");
}