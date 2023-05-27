$(document).ready(function() {
	// set radio buttons
	setDefaults();
	// attach event
	$("#submit-btn").on('click', addSubmission);

});

function setDefaults() {
	let gender = $("#gender_").val();
	let diagnosed = $("#c19_diagnosed_").val();
	if (gender) $("#gender_" + gender.toLowerCase()).prop("checked", true).trigger("click");
	if (diagnosed) $("#c19_diagnosed_" + diagnosed.toLowerCase()).prop("checked", true).trigger("click");
}

async function addSubmission() {

	$("#submit-btn").prop("disabled", true); // disable multiple submission

	// alert message
	let card = $("#resp-msg");
	card.hide();

	// input data
	let full_name = $("#full_name").val();
	let phone = $("#phone").val();
	let birth_date = $("#birth_date").val();
	let gender = $('input[name=genderRadios]:checked').val()
	let address_1 = $("#address_1").val();
	let address_2 = $("#address_2").val();
	let city = $("#city").val();
	let state = $("#state").val();
	let zip = $("#zip").val();
	let health_issues = $("#health_issues").val();
	let symptoms = $("#symptoms").val();
	let allergies = $("#allergies").val();
	let c19_diagnosed = $('input[name=covidRadios]:checked').val()

	const data = {
		full_name: full_name,
		phone: phone,
		birth_date: birth_date,
		gender: gender,
		address_1: address_1,
		address_2: address_2,
		city: city,
		state: state,
		zip: zip,
		health_issues: health_issues,
		symptoms: symptoms,
		allergies: allergies,
		c19_diagnosed: c19_diagnosed
	};

	await fetch('/api/enroll', {
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

	$("#submit-btn").prop("disabled", false);
}