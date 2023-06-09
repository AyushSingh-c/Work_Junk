$(document).ready(function() {

	// set input events
	$("#login-btn").on('click', function() {
		auth('login')
	});
	$("#register-btn").on('click', function() {
		auth('register')
	});
	$("#signin-link").on('click', function() {
		toggleView('login')
	});
	$("#signup-link").on('click', function() {
		toggleView('register')
	});
});

function toggleInputs(state) {
	$("#username").prop("disabled", state);
	$("#password").prop("disabled", state);
	$("#login-btn").prop("disabled", state);
	$("#register-btn").prop("disabled", state);
}

function toggleView(view) {
	if (view == 'login') {
		$("#signup-group").hide();
		$("#register-btn").hide();
		$("#login-btn").show();
		$("#signin-link").attr("class", "nav-link active");
		$("#signup-link").attr("class", "nav-link");
		$("#resp-msg").hide();
		$("#auth-p1").text("Sign in");
	} else {
		$("#signup-group").show();
		$("#register-btn").show();
		$("#login-btn").hide();
		$("#signin-link").attr("class", "nav-link");
		$("#signup-link").attr("class", "nav-link active");
		$("#resp-msg").hide();
		$("#auth-p1").text("Sign up");
	}
}



async function auth(intent) {

	toggleInputs(true); // disable inputs

	// prepare alert
	let card = $("#resp-msg");
	card.hide();


	let user = $("#username").val();
	let pass = $("#password").val();
	let email = $("#email").val();

	// validate
	if ($.trim(user) === '' || $.trim(pass) === '') {
		toggleInputs(false);
		card.text("Please fill out all the required fields!");
		card.attr("class", "alert alert-danger");
		card.show();
		return;
	}

	const data = {
		username: user,
		password: pass
	};
	if (intent == 'register') data["email"] = email;

	await fetch(`/api/${intent}`, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
			},
			body: JSON.stringify(data),
		})
		.then((response) => response.json()
			.then((resp) => {
				if (response.status == 200) {
					card.text(resp.message);
					card.attr("class", "alert alert-success");
					card.show();
					if (intent == 'login') {
						window.location.href = '/home';
					}
					window.setTimeout(function() {
						toggleView('login');
					}, 600);
					return;
				}
				card.text(resp.message);
				card.attr("class", "alert alert-danger");
				card.show();
			}))
		.catch((error) => {
			card.text(error);
			card.attr("class", "alert alert-danger");
			card.show();
		});

	toggleInputs(false); // enable inputs
}