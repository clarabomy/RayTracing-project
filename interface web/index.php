<?php
session_start();

require('global.php');
require('Controller.php');

//$_SESSION = array();
try {
    if (!isset($_GET['action'])) {
        $action = 'edit';
    }
    else if ($_GET['action'] != 'edit' && $_GET['action'] != 'add') {
        throw new Exception("Page indéfinie");//affiche page d'erreur
    }
    else {
        $action = $_GET['action'];
    }

    switch ($action) {
        case 'edit':
            presetEdition();
        break;
        case 'add':
            presetUpdate();
        break;
    }
}
catch(Exception $error) {//retravailler
    $errorMessage = $error->getMessage();
    $errorDetail = 'Fichier : ' . $error->getFile() . ', ligne ' . $error->getLine();
    
    require('View/vError.php');
}