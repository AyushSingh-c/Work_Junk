const JWTHelper = require('../helpers/JWTHelper');

module.exports = async (req, res, next) => {
	try{
		if (req.cookies.session === undefined) {
			if(!req.is('application/json')) return res.redirect('/');
			return res.status(401).json({ message: 'Authentication required!' });
		}
		let data = JWTHelper.decode(req.cookies.session);
		req.data = {
			email: data.email
		}
		next();
	} catch(e) {
		return res.status(500).send('Internal server error');
	}
}