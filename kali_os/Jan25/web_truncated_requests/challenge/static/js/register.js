$(document).ready(() => {
	$('#register-btn').on('click', register);

	$('#username').on('keydown', () => {
		$('#resp-msg').hide()
	});

	$('#password').on('keydown', () => {
		$('#resp-msg').hide()
	});
});

const register = async () => {

	let card = $("#resp-msg");
	card.attr("class", "alert alert-info");
	card.hide();

	let user = $("#username").val();
	let pass = $("#password").val();

	if ($.trim(user) === '' || $.trim(pass) === '') {
		toggleInputs(false);
		card.text("Please input email and password first!");
		card.attr("class", "alert alert-danger");
		card.show();
		return;
	}

	await fetch('/api/register', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
			},
			body: JSON.stringify({
                username: user,
                password: pass
            }),
		})
		.then((response) => response.json()
			.then((resp) => {
				card.attr("class", "alert alert-danger");
				if (response.status == 200) {
					card.attr("class", "alert alert-success");
                    setTimeout(() => {
                        window.location.href = '/';
                    }, 1500);
				}
				card.text(resp.message);
				card.show();
			}))
		.catch((error) => {
			card.text(error);
			card.attr("class", "alert alert-danger");
			card.show();
		});
}