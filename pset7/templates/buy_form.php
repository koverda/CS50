<div id = "nav">
    <ul class="nav nav-pills">
        <li><a href="/">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>

<div>
    <h2>
        Buy Stocks
    </h2>
</div>

<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="Stock Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Number of Shares" type="number"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Buy</button>
        </div>
    </fieldset>
</form>
