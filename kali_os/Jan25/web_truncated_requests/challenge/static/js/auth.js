$(document).ready(() => {
	$('#login-btn').on('click', login);

	$('#username').on('keydown', () => {
		$('#resp-msg').hide()
	});

	$('#password').on('keydown', () => {
		$('#resp-msg').hide()
	});
});

const login = async () => {

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

	await fetch('/api/login', {
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
					window.location.href = '/dashboard';
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