<nav class="ink-navigation vspace">
	<ul class="menu horizontal black rounded shadowed">
	    <li><a href="index.php">Accueil</a></li>
	    <?php 
	    	if (isset($_COOKIE['login']) && isset($_COOKIE['password']) ){
	    		$check=$bdd->prepare("SELECT login, password FROM users");
	    		$check->execute();
	    		$data=$check->fetch();
	    		$check->closeCursor();
	    		if($_COOKIE['login']==$data['login'] && $_COOKIE['password']==$data['password']){
	    ?>			
	    			<li><a href="search.php">Search</a></li>
	    			<li><a href="add.php">Add</a></li>
	            	<li><a href="delete.php">Delete</a></li>
	    <?php		if($_COOKIE['login']== 'admin'){
	    ?>        		<li><a href="administration.php">Administration</a></li>
	    <?php		} ?>
	    			<li>
	        			<form action="redirect.php" method="POST">
	            			<input type="hidden" value="logout" name="logout">
	            			<input type="submit"  class='ink-button' value="Deconnexion">
	        			</form>
	            	</li>
	     <?php }
	     	} ?>
	</ul>
</nav>