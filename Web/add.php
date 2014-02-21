<!DOCTYPE html>
<html lang="fr">
    
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
        <title>
            Ajout d'un capteur
        </title>
        <meta name="description" content="">
        <meta name="author" content="Maliar Benoit, Maurice Thomas">
        <meta name="HandheldFriendly" content="True">
        <meta name="MobileOptimized" content="320">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
        <link rel="shortcut icon" href="/ink/img/polytech.ico">
        <link rel="apple-touch-icon-precomposed" href="/ink/img/touch-icon.57.png">
        <link rel="apple-touch-icon-precomposed" sizes="72x72" href="/ink/img/touch-icon.72.png">
        <link rel="apple-touch-icon-precomposed" sizes="114x114" href="/ink/img/touch-icon.114.png">
        <link rel="apple-touch-startup-image" href="/ink/img/splash.320x460.png"
        media="screen and (min-device-width: 200px) and (max-device-width: 320px) and (orientation:portrait)">
        <link rel="apple-touch-startup-image" href="/ink/img/splash.768x1004.png"
        media="screen and (min-device-width: 481px) and (max-device-width: 1024px) and (orientation:portrait)">
        <link rel="apple-touch-startup-image" href="/ink/img/splash.1024x748.png"
        media="screen and (min-device-width: 481px) and (max-device-width: 1024px) and (orientation:landscape)">
        <link rel="stylesheet" type="text/css" href="/ink/css/ink.css">
        
        <!--[if IE 7 ]>
            <link rel="stylesheet" href="/ink/css/ink-ie7.css" type="text/css" media="screen" title="no title" charset="utf-8">
        <![endif]-->
        
        <script type="text/javascript" src="/ink/js/holder.js"></script>
        <script type="text/javascript" src="/ink/js/ink.min.js"></script>
        <script type="text/javascript" src="/ink/js/ink-ui.min.js"></script>
        <script type="text/javascript" src="/ink/js/autoload.js"></script>
        <script type="text/javascript" src="/ink/js/html5shiv.js"></script>
        
        
        <style type="text/css">
       		body {
                background: #ededed;
            }
            header {
                padding: 2em 0;
                margin-bottom: 2em;
            }
            header h1 {
                font-size: 2em;
            }
            header h1 small:before  {
                content: "|";
                margin: 0 0.5em;
                font-size: 1.6em;
            }
            footer {
                background: #ccc;
                color: #0003;
            }
            footer p {
                padding: 0.5em 1em 0.5em 0;
                margin: 0;        
            }

        </style>
    </head>
    
	<body>
		<div class="ink-grid">
            <header>
                <h1>Ajouter un capteur<small></small></h1>
                <nav class="ink-navigation vspace">
                    <ul class="menu horizontal black rounded shadowed">
                        <li><a href="../">Accueil</a></li>
                        <li class="active"><a href="#">Ajout</a></li>
                    </ul>
                </nav>             
            </header>
            
        <div class="column-group gutters">
        	<div class="ink-form large-50 medium-50 small-100">
        		<?php
        			if(isset($_POST['login']) && isset($_POST['pass'])){
        				$req=$bdd->prepare("SELECT login, ///// FROM admin")
        				if($_POST['login'])
        		?>
			        <div class="control-group required column-group gutters">
		                            <label for="email" class="large-20 content-right">Name</label>
		                            <div class="control large-40">
		                                <input type="text" id="email">
		                                <p class="tip">First Name</p>
		                            </div>
		                            <div class="control large-40">
		                                <input type="text" id="email">
		                                <p class="tip">Last Name</p>
		                            </div>
		            </div>
		       <?php } ?>
        	</div>
        </div>
	</body>
</html>