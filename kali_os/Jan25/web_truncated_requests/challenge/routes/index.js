const express        = require('express');
const router         = express.Router();
const JWTHelper      = require('../helpers/JWTHelper');
const AuthMiddleware = require('../middleware/AuthMiddleware');

let db;

const response = data => ({ message: data });

router.get('/', (req, res) => {
	return res.render('login.html');
});

router.get('/register', (req, res) => {
	return res.render('register.html');
});

router.post('/api/register', async (req, res) => {
	const { username, password } = req.body;

	if (username && password) {
		return db.getUser(username)
			.then(user => {
				if (user.length) return res.status(401).send(response('User already registered!'));

				return db.registerUser(username, password)
					.then(() => res.send(response('User registered successfully!')))
                    .catch(() => res.send(response('Something went wrong!')));
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
				if (!user.length) return res.status(403).send(response('Invalid username or password!'));

				JWTHelper.sign({ username: user[0].username })
					.then(token => {
						res.cookie('session', token, { maxAge: 43200000 });
						res.send(response('User authenticated successfully!'));
					})
			})
			.catch(() => res.status(403).send(response('Invalid username or password!')));
	}

	return res.status(500).send(response('Missing parameters!'));
});

router.get('/dashboard', AuthMiddleware, async (req, res, next) => {

    return db.getUser(req.data.username)
        .then(async user => {
            let approved = await db.listProducts(1);
            let unapproved = user[0].username == 'admin' ? await db.listProducts(0) : null;

            return res.render('dashboard.html', { user: user[0], approved, unapproved });
        })
        .catch(() => res.redirect('/'));

});

router.get('/logout', (req, res) => {
	res.clearCookie('session');

	return res.redirect('/');
});

module.exports = database => {
	db = database;
	return router;
};