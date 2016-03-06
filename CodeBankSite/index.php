<?php include 'header.php' ?>
            <div class="account-wall">
                <?php 
                if (!empty($_GET['error'])) {
                    ?> <div class="alert alert-danger" role="alert">Invalid Credentials!</div><?php
                }
                ?>
                <form method="POST" class="form-signin" action="session.php">
                <input class="form-control" id="username" name="username" placeholder="username" required autofocus>
                <input type="password" class="form-control" id="password" name="password" placeholder="Password" required>
                <button class="btn btn-lg btn-primary btn-block" type="submit" id="signIn">
                    Sign in</button>
               
                <a href="#" class="pull-right need-help">Need help? </a><span class="clearfix"></span>
                </form>
            </div>
            <a href="#" class="text-center new-account">Create an account </a>
             <br>
             <h2>
            <p>Οr sign in with codeBank wearable</p>
             </h2>
              <div class="row">
                    <div class="col-sm-6 col-md-4 col-md-offset-4" >
                        <img src="static/wearable.jpg" id="iconWearable" />
                    </div>
        </div>

<script >
$(function() {
    var url = 'checkBank.php';
    var receivedSuccess = false;
    (function worker() {
        if (receivedSuccess) {
            return;
        }
      $.ajax({
        url: url, 
        success: function(data) {
            console.log(data);
            if (data.trim() === 'success') {
                receivedSuccess = true;
                alert('Successful Login');
                $('.form-signin').submit();
            }
        },
        complete: function() {
          // Schedule the next request when the current one's complete
          setTimeout(worker, 2000);
        }
      });
    })();

});
</script>

<?php include 'footer.php' ?>

