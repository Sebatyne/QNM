#include "NotesExporter.h"

namespace NM{
    QString LaTexNotesExporter::NoteToLatex(Note * ConvertedNote, unsigned int titleLevel){
        QString latexExport;
        (titleLevel > titleSize.size() - 1) ? titleLevel = titleSize.size() - 1 : titleLevel;
        if(ConvertedNote->getType() == Note::Document){
            Document * tdoc = dynamic_cast<Document*>(ConvertedNote);
            if(tdoc){

                if(titleLevel > 0){
                    latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + tdoc->getTitle() + "}\n\n";
                }

                Document::Iterator it = tdoc->begin();

                for(; it != tdoc->end(); it++){
                    latexExport += NoteToLatex(*it, titleLevel + 1);
                }

                if(delimitParts){
                    latexExport += "\\rule{\\linewidth}{.5pt}\n\n";
                }

            }
        }
        else if(ConvertedNote->getType() == Note::NArticle)
        {
            NArticle * tArt = dynamic_cast<NArticle*>(ConvertedNote);
            if(tArt){
                latexExport += ArticleToLatex(tArt, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NImage){
            NImage * tIm = dynamic_cast<NImage*>(ConvertedNote);
            if(tIm){
                latexExport += ImageToLatex(tIm, titleLevel);
            }
        }
        else if(!ignoreAudio && ConvertedNote->getType() == Note::NAudio)
        {
            NAudio * tAud = dynamic_cast<NAudio*>(ConvertedNote);
            if(tAud){
                latexExport += AudioToLatex(tAud, titleLevel);
            }
        }
        else if(!ignoreVideo && ConvertedNote->getType() == Note::NVideo){
            NVideo * tVid = dynamic_cast<NVideo*>(ConvertedNote);
            if(tVid){
                latexExport += VideoToLatex(tVid, titleLevel);
            }
        }
        return latexExport;
    }

    QString LaTexNotesExporter::ArticleToLatex(NArticle * ConvertedArticle, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedArticle->getTitle() + "}";
        }
        latexExport += ConvertedArticle->getText() + "\\\\";

        return latexExport;
    }

    QString LaTexNotesExporter::ImageToLatex(NImage * ConvertedImage, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedImage->getTitle() + "}\n\n";
        }
        latexExport += "\\begin{figure}[h!]\n";
        latexExport += "\\centering\n";
        latexExport += "\\includegraphics[scale = 1]{" + ConvertedImage->getUrl() + "}\n";
        latexExport += "\\caption{" + ConvertedImage->getDescription() + "}";
        latexExport += "\\end{figure}\n\n";

        return latexExport;
    }

    QString LaTexNotesExporter::AudioToLatex(NAudio * ConvertedAudio, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedAudio->getTitle() + "}\n\n";
        }
        latexExport += "\\begin{figure}[h!]\n";
        latexExport += "\\centering\n";
        latexExport += "\\includegraphics[scale = 0.5]{aud.jpg}\n";
        latexExport += "\\caption{Fichier Audio"+ ConvertedAudio->getDescription() +"\\\\Ecouter: "+ ConvertedAudio->getUrl() +"}\n";
        latexExport += "\\end{figure}\n\n";

        return latexExport;
    }

    QString LaTexNotesExporter::VideoToLatex(NVideo * ConvertedVideo, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedVideo->getTitle() + "}\n\n";
        }
        latexExport += "\\begin{figure}[h!]\n";
        latexExport += "\\centering\n";
        latexExport += "\\includegraphics[scale = 0.5]{vid.jpg}\n";
        latexExport += "\\caption{Fichier Video : "+ ConvertedVideo->getDescription() +"\\\\Regarder: "+ ConvertedVideo->getUrl() +"}\n";
        latexExport += "\\end{figure}\n\n";

        return latexExport;
    }

    QString LaTexNotesExporter::getRawExport(){
        QString latexExport = "\\documentclass[12pt,a4paper]{article}\n"; // Changer Article par le type de document choisi
        latexExport += "\\usepackage[latin1]{inputenc}\n";
        latexExport += "\\usepackage[T1]{fontenc}\n";
        latexExport += "\\usepackage[francais]{babel}\n";
        latexExport += "\\usepackage{courier}\n";
        latexExport += "\\usepackage{caption}\n";
        latexExport += "\\usepackage{graphicx}\n";
        latexExport += "\\usepackage[top=1cm, bottom=2cm, right=1.5cm, left=1.5cm]{geometry}\n\n";
        latexExport += "\\title{"+ ExportedNote->getTitle() +"}\n\n";

         latexExport += "\\date{";
        if(displayDate){
            latexExport += "\\date\\today";
        }
        latexExport += "}";

        latexExport += "\\begin{document}\n\n";
        latexExport += "\\maketitle\n\n";
        latexExport += NoteToLatex(this->ExportedNote, 0);

        latexExport += "\\end{document}";

        return latexExport;
    }



    /*class textNotesExporter : NotesExporter{
    public:
        textNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){}
        QString getRawExport();
    };*/


    QString textNotesExporter::NoteToText(Note * ConvertedNote, unsigned int titleLevel){
        QString textExport;
        if(ConvertedNote->getType() == Note::Document){
            Document * tdoc = dynamic_cast<Document*>(ConvertedNote);
            if(tdoc){

                textExport += "\n";

                if(titleLevel > 0){
                    textExport += NUtils::repeat(titleLevel, "\t") + "[" + tdoc->getTitle() + "]\n\n";
                }

                Document::Iterator it = tdoc->begin();

                for(; it != tdoc->end(); it++){
                    textExport += NoteToText(*it, titleLevel + 1);
                }

                if(delimitParts){
                    textExport += "_________________________________________________________________________________\n\n";
                }

            }
        }
        else if(ConvertedNote->getType() == Note::NArticle)
        {
            NArticle * tArt = dynamic_cast<NArticle*>(ConvertedNote);
            if(tArt){
                textExport += ArticleToText(tArt, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NImage){
            NImage * tIm = dynamic_cast<NImage*>(ConvertedNote);
            if(tIm){
                textExport += ImageToText(tIm, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NAudio)
        {
            NAudio * tAud = dynamic_cast<NAudio*>(ConvertedNote);
            if(tAud){
                textExport += AudioToText(tAud, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NVideo){
            NVideo * tVid = dynamic_cast<NVideo*>(ConvertedNote);
            if(tVid){
                textExport += VideoToText(tVid, titleLevel);
            }
        }
        return textExport;
    }

    QString textNotesExporter::ArticleToText(NArticle * ConvertedArticle, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedArticle->getTitle() + "]\n";
        }
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedArticle->getText() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::ImageToText(NImage * ConvertedImage, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedImage->getTitle() + "]\n\n";
        }
        textExport += NUtils::repeat(titleLevel, "\t") + "Voir " + ConvertedImage->getUrl() + "\n";
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedImage->getDescription() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::AudioToText(NAudio * ConvertedAudio, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedAudio->getTitle() + "]\n\n";
        }

        textExport += NUtils::repeat(titleLevel, "\t") + "Ecouter " + ConvertedAudio->getUrl() + "\n";
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedAudio->getDescription() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::VideoToText(NVideo * ConvertedVideo, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedVideo->getTitle() + "]\n\n";
        }

        textExport += NUtils::repeat(titleLevel, "\t") + "Regarder " + ConvertedVideo->getUrl() + "\n";
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedVideo->getDescription() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::getRawExport(){
        QString textExport = NUtils::repeat(5, "\t") + " ********** " +ExportedNote->getTitle() + " **********\n";
        if(displayDate){
            textExport += "Le @@@@@@@@ \n\n"; //Remplacer par la date
        }
        textExport += "\n\n";

        textExport += NoteToText(this->ExportedNote, 0);

        return textExport;
    }


    QString HTMLNotesExporter::NoteToHTML(Note * ConvertedNote, unsigned int titleLevel){
        QString HTMLExport;
        (titleLevel > 6) ? titleLevel = 5 : titleLevel;
        if(ConvertedNote->getType() == Note::Document){
            Document * tdoc = dynamic_cast<Document*>(ConvertedNote);
            if(tdoc){
                if(titleLevel > 0){
                    HTMLExport += "<h" + QString::number(titleLevel + 1) + ">" + ConvertedNote->getTitle() + "</h" + QString::number(titleLevel + 1) +">";
                }

                HTMLExport += "<div class=\"subnote\">";

                Document::Iterator it = tdoc->begin();

                for(; it != tdoc->end(); it++){
                    HTMLExport += NoteToHTML(*it, titleLevel + 1);
                }

                HTMLExport += "</div>";

                if(delimitParts){
                    HTMLExport += "<div class=\"hbar\"></div>";
                }

            }
        }
        else if(ConvertedNote->getType() == Note::NArticle)
        {
            NArticle * tArt = dynamic_cast<NArticle*>(ConvertedNote);
            if(tArt){
                HTMLExport += ArticleToHTML(tArt, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NImage){
            NImage * tIm = dynamic_cast<NImage*>(ConvertedNote);
            if(tIm){
                HTMLExport += ImageToHTML(tIm, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NAudio)
        {
            NAudio * tAud = dynamic_cast<NAudio*>(ConvertedNote);
            if(tAud){
                HTMLExport += AudioToHTML(tAud, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NVideo){
            NVideo * tVid = dynamic_cast<NVideo*>(ConvertedNote);
            if(tVid){
                HTMLExport += VideoToHTML(tVid, titleLevel);
            }
        }
        return HTMLExport;
    }

    QString HTMLNotesExporter::ArticleToHTML(NArticle * ConvertedArticle, unsigned int titleLevel){
        QString HTMLExport = "";
        if(titleLevel){
            HTMLExport += "<span>"+ ConvertedArticle->getTitle() +"</span>\n";
        }
        HTMLExport += "<p>"+ ConvertedArticle->getText() +"</p>\n";

        return HTMLExport;
    }

    QString HTMLNotesExporter::ImageToHTML(NImage * ConvertedImage, unsigned int titleLevel){
        QString HTMLExport = "";
        if(titleLevel){
            HTMLExport += "<span>"+ ConvertedImage->getTitle() +"</span>\n";
        }

        HTMLExport += "<img src=\""+ ConvertedImage->getUrl() +"\">\n";
        HTMLExport += "<legend>- <i>Illustration</i> : "+ ConvertedImage->getDescription() +" -</legend>\n";

        return HTMLExport;
    }

    QString HTMLNotesExporter::AudioToHTML(NAudio * ConvertedAudio, unsigned int titleLevel){
        QString HTMLExport = "";
        if(titleLevel){
            HTMLExport += "<span>"+ ConvertedAudio->getTitle() +"</span>\n";
        }

        HTMLExport += "<audio controls><source src=\""+ ConvertedAudio->getUrl() +"\"></audio>\n";
        HTMLExport += "<legend>- <i>Source audio</i> : "+ ConvertedAudio->getDescription() +" -</legend>\n";

        return HTMLExport;
    }

    QString HTMLNotesExporter::VideoToHTML(NVideo * ConvertedVideo, unsigned int titleLevel){
        QString HTMLExport = "";
        if(titleLevel){
            HTMLExport += "<span>"+ ConvertedVideo->getTitle() +"</span>\n";
        }

        HTMLExport += "<video controls src=\""+ ConvertedVideo->getUrl() +"\"></video>\n";
        HTMLExport += "<legend>- <i>Source audio</i> : "+ ConvertedVideo->getDescription() +" -</legend>\n";

        return HTMLExport;
    }

    QString HTMLNotesExporter::getRawExport(){
        QString HTMLExport = "<html>\n";
        HTMLExport += "<head>\n";
        HTMLExport += "<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n";
        HTMLExport += "<style>\n";
        HTMLExport += CSS;
        HTMLExport += "</style>\n";
        HTMLExport += "</head>\n";
        HTMLExport += "<body>\n";
        HTMLExport += "<div id=\"content\">\n";
        HTMLExport += "<h1>"+ ExportedNote->getTitle() + "\n";
        if(displayDate){
            QString date = QDate::currentDate().toString("dd/MM/yyyy");
            HTMLExport += "<div class=\"date\">Exporté le "+ date +"</div>\n";
        }
        HTMLExport += "</h1>\n";

        HTMLExport += NoteToHTML(ExportedNote, 0);

        HTMLExport += "</div>\n";
        HTMLExport += "</body>\n";
        HTMLExport += "</html>\n";

        return HTMLExport;
    }


}
