from dotenv import load_dotenv
import os

load_dotenv()
HOST = os.getenv("url")
PORT = int(os.getenv("port"))
USER = os.getenv("user")
PASSWORD = os.getenv("pass")