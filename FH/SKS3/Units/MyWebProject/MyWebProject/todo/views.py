from django.shortcuts import render
from todo.models import todo
from django.http import HttpResponse
from django.template import RequestContext, loader

# Create your views here.
def index(request):
    todo_list = todo.objects.all()
    template = loader.get_template('todo/index.html')
    context = {
        'todo_list': todo_list,
        
    }
    return HttpResponse(template.render(context))
