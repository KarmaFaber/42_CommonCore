#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import cgi
import cgitb
import os
from datetime import datetime
import sys

cgitb.enable()

sys.stdout.write("Content-Type: text/html; charset=utf-8\r\n\r\n")
sys.stdout.flush()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
COMMENTS_FILE_PATH = os.path.abspath(os.path.join(SCRIPT_DIR, '..', 'data', 'comments.txt'))

form = cgi.FieldStorage()
username = form.getvalue("username")
subject = form.getvalue("subject")
comment = form.getvalue("comment")

success = False

if all([username, subject, comment]):
	try:
		os.makedirs(os.path.dirname(COMMENTS_FILE_PATH), exist_ok=True)
		
		comment_id = int(datetime.now().timestamp() * 1e6)
		timestamp = datetime.now().strftime("%Y-%m-%d")

		with open(COMMENTS_FILE_PATH, 'a') as f:
			clean_comment = comment.replace('\n', ' ').replace('\r', '')
			f.write(f"{comment_id}|{timestamp}|{username}|{subject}|{clean_comment}\n")
		success = True
	except Exception as e:
		error_msg = f"Storage Error: {str(e)}"
else:
	error_msg = "Validation Error: All fields are required."

if success:
	print(f"""<!DOCTYPE html>
	<html lang="en">
	<head>
		<meta charset="UTF-8">
		<title>Success - Webserv</title>
		<link rel="stylesheet" href="/css/style.css">
	</head>
	<body>
		<main style="text-align: center; padding-top: 10vh; min-height: calc(100vh - 150px);">
			<h1 class="main-title"><span class="gradient-text">Message Posted</span></h1>
			<section class="form-container" style="max-width: 500px; margin-top: 30px;">
				<div class="comment-form" style="border-color: var(--neon-start, #00FFFF); text-align: center; padding: 40px;">
					<p style="font-size: 20px; color: var(--neon-start, #00FFFF); margin-bottom: 15px;">Comment Broadcasted</p>
					<p style="color: var(--text-light); line-height: 1.6; margin-bottom: 25px;">
						Your log entry has been successfully parsed and appended to the data repository.
					</p>
					<div style="display: flex; flex-direction: column; gap: 15px;">
						<a href="/cgi-bin/comments_view.py" class="submit-button-neon" style="text-decoration: none; display: inline-block; text-align: center; margin: 0;">
							View Messagesboard (GET)
						</a>
						<a href="/comments.html" style="color: var(--text-subtle); text-decoration: none; font-size: 14px; transition: color 0.3s;" onmouseover="this.style.color='#fff'" onmouseout="this.style.color='var(--text-subtle)'">
							&larr; Write another comment
						</a>
					</div>
				</div>
			</section>
		</main>
		<footer class="main-footer">
			<div class="footer-container">
				<p class="footer-copy">&copy; 2026 Webserv.</p>
			</div>
		</footer>
	</body>
	</html>
	""")
else:
	print(f"""<!DOCTYPE html>
	<html lang="en">
	<head>
		<meta charset="UTF-8">
		<title>Error - Webserv</title>
		<link rel="stylesheet" href="/css/style.css">
	</head>
	<body>
		<main style="text-align: center; padding-top: 10vh; min-height: calc(100vh - 150px);">
			<h1 class="main-title"><span class="gradient-text">Submission Failed</span></h1>
			<section class="form-container" style="max-width: 500px; margin-top: 30px;">
				<div class="comment-form" style="border-color: var(--neon-end, #FF00FF); text-align: center; padding: 40px;">
					<p style="font-size: 20px; color: var(--neon-end, #FF00FF); margin-bottom: 15px;">Transaction Aborted</p>
					<p style="color: var(--text-subtle); line-height: 1.6; margin-bottom: 25px; font-style: italic;">
						{error_msg}
					</p>
					<a href="/comments.html" class="submit-button-neon" style="text-decoration: none; display: inline-block; text-align: center; margin: 0; background: linear-gradient(90deg, var(--neon-end), #8681ec);">
						Return to Form
					</a>
				</div>
			</section>
		</main>
		<footer class="main-footer">
			<div class="footer-container">
				<p class="footer-copy">&copy; 2026 Webserv.</p>
			</div>
		</footer>
	</body>
	</html>
	""")
