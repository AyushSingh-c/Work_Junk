const express        = require('express');
const router         = express.Router();
const JWTHelper      = require('../helpers/JWTHelper');
const AuthMiddleware = require('../middleware/AuthMiddleware');


let db;

const response = data => ({ message: data });

router.get('/', (req, res) => {
	return res.render('index.html');
});

router.post('/api/register', async (req, res) => {

	const { username, password, email } = req.body;

	if (username && password && email) {
		return db.checkUser(username, email)
			.then(user => {
				if (user) return res.status(401).send(response('User already registered!'));
				return db.registerUser(username, password, email)
					.then(()  => res.send(response('User registered successfully!')))
			})
			.catch(() => res.send(response('Something went wrong!')));
	}
	return res.status(401).send(response('Please fill out all the required fields!'));
});

router.post('/api/login', async (req, res) => {

	const { username, password } = req.body;

	if (username && password) {
		return db.loginUser(username, password)
			.then(user => {
				let token = JWTHelper.sign({ email: user.email });
				res.cookie('session', token, { maxAge: 3600000 });
				return res.send(response('User authenticated successfully!'));
			})
			.catch(() => res.status(403).send(response('Invalid username or password!')));
	}
	return res.status(500).send(response('Missing parameters!'));
});

router.get('/home', AuthMiddleware, async (req, res, next) => {

	return db.getUser(req.data.email)
		.then(user => {
			if (user === undefined) return res.redirect('/');
			return db.getFormData(user.username)
				.then(formData => { 
					if (user.username == "admin") {
						return db.getStats()
						.then(adminStats => {
							return res.render('form.html', { formData, adminStats });
						})
					} 
					res.render('form.html', { formData });
				})
		})
		.catch(() => res.status(500).send(response('Something went wrong!')));
});

router.post('/api/enroll', AuthMiddleware, async (req, res) => {

	return db.getUser(req.data.email)
		.then(user => {
			if (user === undefined) return res.redirect('/'); 
			const jsonData = req.body;
			if (jsonData) {
				return db.addRecord(jsonData,user.username)
					.then(()  => res.send(response('Your submission is saved successfully!')))	
			}
			return res.status(403).send(response('Missing parameters!'));
		})
		.catch(() => res.status(500).send(response('Something went wrong!')));
});

router.get('/logout', (req, res) => {
	res.clearCookie('session');
	return res.redirect('/');
});

module.exports = database => { 
	db = database;
	return router;
};