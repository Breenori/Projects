from django.db import models


class ScriptTypes(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50)

# Create your models here.
class ScriptLangs(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50)
    desc = models.TextField()
    type = models.ForeignKey(ScriptTypes, on_delete=models.CASCADE)

class ScriptLangsAdd(models.Model):
    id = models.AutoField(primary_key=True)
    info = models.TextField()
    lang = models.ForeignKey(ScriptLangs, on_delete=models.CASCADE)

