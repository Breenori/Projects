from django.conf.urls import url
from SKSApp import views

urlpatterns = [
    url(r'^$', views.index, name='index')    
]