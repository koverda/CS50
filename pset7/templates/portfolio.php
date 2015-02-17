<div id = "nav">
    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>
<div>
    <h2>
        Portfolio
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
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
            </tr>
        </thead>
        <tbody>  
            <?php foreach ($positions as $position): ?>

                <tr>
                    <td><?= strtoupper($position["symbol"]) ?></td>
                    <td><?= $position["name"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td><?= "$" . format_number($position["price"]) ?></td>
                </tr>

            <?php endforeach ?>
        </tbody>
    </table>
</div>

