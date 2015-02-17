<ul class="nav nav-pills">
    <li><a href="/">Portfolio</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>


<div>
    <h3>
        <?php
            print("Quote for " . $stock["name"]);
        ?>            
    </h3>
    <?php
        print("Symbol: " . $stock["symbol"] );   
    ?> 
    <br/>
    <?php
        print(" Price: $" . format_number($stock["price"]));
    ?>
    
<br/>
<br/>
</div>

<!-- HTML form to look up another stock   --> 
<form action="quote.php" method="post">

    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="Stock Symbol" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Recive Quote</button>
        </div>

    </fieldset>
</form>
<div>
    or <a href="logout.php">log out</a>
</div>
