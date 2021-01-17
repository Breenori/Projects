from django.shortcuts import render
from SKSApp.models import ScriptTypes, ScriptLangs, ScriptLangsAdd
from django.http import HttpResponse
from django.template import RequestContext, loader

# Create your views here.
def index(request):
    type_list = ScriptTypes.objects.all()
    lang_list = ScriptLangs.objects.all()
    info_list = ScriptLangsAdd.objects.all()

    template = loader.get_template('SKSApp/index.html')
    context = {
        'lang_list': lang_list,
        'type_list': type_list,
        'info_list': info_list
    }
    return HttpResponse(template.render(context))
