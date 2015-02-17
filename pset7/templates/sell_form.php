<div id = "nav">
    <ul class="nav nav-pills">
        <li><a href="/">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>


<form action="sell.php" method="post">
    <fieldset>
        <div>
        Select stock to sell:
        </div>
        <div class="form-group">

            <select class="form-control" name="symbol">
                <option value=""> </option>
                
                <?php
                    foreach($symbols as $symbol)
                    {
                        print "<option value=\"".
                        strtoupper($symbol["symbol"]) . 
                        "\">" . 
                        strtoupper($symbol["symbol"]) .
                        "</option>\n";    
                    }
                ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
