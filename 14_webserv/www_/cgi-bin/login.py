#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import cgi
import cgitb
import os
from datetime import datetime, timedelta

# Enable debugging to show detailed errors in the browser during webserver development
cgitb.enable()

session = os.environ.get('BONUS_SESSION', '').strip()

# 1. Parse the form data sent via POST
form = cgi.FieldStorage()
username = form.getvalue("username")
email = form.getvalue("email")

# 2. Generate session
if len(session) == 0:
	# Generate parameters for the successful session cookie
	# expires = (datetime.utcnow() + timedelta(days=1)).strftime("%a, %d-%b-%Y %H:%M:%S GMT")
	
	# --- Mandatory HTTP headers for the cookies bonus ---
	print("Status: 200 OK")
	print("Bonus-Create-Session: yes")
	print(f"Bonus-Username: {username}")
	print(f"Bonus-Email: {email}")
	print("Content-Type: text/html; charset=utf-8")
	# print(f"Set-Cookie: session_id={"placehoder"}; Expires={expires}; Path=/; HttpOnly")
	print() # Required blank line that separates headers from body
	
	# Show the success page integrated with the design
	print(f"""
	<!DOCTYPE html>
	<html lang="en">
	<head>
		<meta charset="UTF-8">
		<title>Dashboard - Webserv</title>
		<link rel="stylesheet" href="/css/style.css">
	</head>
	<body>
		<main style="text-align: center; padding-top: 10vh;">
			<h1 class="main-title"><span class="gradient-text">Welcome back!</span></h1>
			<section class="form-container" style="max-width: 500px; margin-top: 30px;">
				<div class="comment-form" style="border-color: #00FFFF; text-align: center;">
					<p style="font-size: 18px; color: #00FFFF;">Login Successful</p>
					<p style="color: var(--text-light); margin: 15px 0;">Your session has been initialized via HTTP Cookies.</p>
					<a href="/index.html" class="submit-button-neon" style="text-decoration: none; display: inline-block; margin-top: 20px; text-align: center;">Go to Home</a>
				</div>
			</section>
		</main>
	</body>
	</html>
	""")
else: #already logged in, redirect to profile CGI
	print("Status: 302 Found")
	print("Location: /cgi-bin/profile.py")
	print()