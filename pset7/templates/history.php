<div id = "nav">
    <ul class="nav nav-pills">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>
<div>
    <h2>
        History
    </h2>
</div>

<div>
    <?php
        print($_SESSION["username"] . "'s Cash: " . format_number($_SESSION["cash"]));
    ?>  
</div>

<div>
    <table class="table table-striped"> 
        <thead>
            <tr>
                <th>Timestamp</th>
                <th>Action</th>
                <th>Symbol</th>
                <th>Name</th>
                <th>Price</th>
                <th>Shares</th>
            </tr>
        </thead>
        <tbody>  
            <?php foreach ($transactions as $transaction): ?>
                <tr>
                    <td><?= $transaction["timestamp"] ?></td>
                    <td><?= strtoupper($transaction["buysell"]) ?></td>
                    <td><?= strtoupper($transaction["symbol"]) ?></td>
                    <td><?= $transaction["name"] ?></td>
                    <td><?= "$" . format_number($transaction["price"]) ?></td>
                    <td><?= $transaction["shares"] ?></td>
                </tr>

            <?php endforeach ?>
        </tbody>
    </table>
</div>

