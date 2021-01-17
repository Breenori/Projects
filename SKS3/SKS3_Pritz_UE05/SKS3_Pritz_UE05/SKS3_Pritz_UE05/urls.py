"""
Definition of urls for SKS3_Pritz_UE05.
"""

from datetime import datetime
from django.urls import path, include
from django.contrib import admin
from django.contrib.auth.views import LoginView, LogoutView


urlpatterns = [
    path('admin/', admin.site.urls),
    path('SKSApp/', include('SKSApp.urls'))
]
