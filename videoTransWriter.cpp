#include "videoTransWriter.h"


videoTransWriter::videoTransWriter()
{
    processedFrameNum = 0;
    stopFlag = false;
    startFrameIndex = 0;
    endFrameIndex = 0;
    totalFrameNum = 0;
    writedFrameNum = 0;
    videoEndFlag = false;
}


videoTransWriter::~videoTransWriter()
{
}

bool videoTransWriter::setInputFileName(string filename)
{
    if (_access(filename.c_str(),0)==-1)
    {
        cout << "No file named " << filename << endl;
        return false;
    }
    inputFileName = filename;
    return true;
}

bool videoTransWriter::setOutputFileName(string filename)
{
    outPutFileName = filename;
    return true;
}

bool videoTransWriter::initTransWriter()
{
    int ret = 0,i=0;
    cstrInputFileName = const_cast<char*>(inputFileName.c_str());
    cstrOutputFileName = const_cast<char*>(outPutFileName.c_str());

    av_register_all();
    //Input
    if ((avformat_open_input(&ifmt_ctx, inputFileName.c_str(), 0, 0)) < 0)
    {
        printf("Could not open input file.");
        goto end;
    }
    if (avformat_find_stream_info(ifmt_ctx, 0) < 0)
    {
        printf("Failed to retrieve input stream information");
        goto end;
    }
    av_dump_format(ifmt_ctx, 0, inputFileName.c_str(), 0);
    //Output
    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, outPutFileName.c_str());

    if (!ofmt_ctx)
    {
        printf("Could not create output context\n");
        ret = AVERROR_UNKNOWN;
        goto end;
    }

    ofmt = ofmt_ctx->oformat;
    for (i = 0; i < ifmt_ctx->nb_streams; i++)
    {
        //Create output AVStream according to input AVStream
        AVStream *in_stream = ifmt_ctx->streams[i];
        AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
        if (!out_stream)
        {
            printf("Failed allocating output stream\n");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        //Copy the settings of AVCodecContext
        if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0)
        {
            printf("Failed to copy context from input to output stream codec context\n");
            goto end;
        }
        out_stream->codec->codec_tag = 0;
        if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
            out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
    }

    //Output information------------------
    av_dump_format(ofmt_ctx, 0, outPutFileName.c_str(), 1);
    //Open output file
    if (!(ofmt->flags & AVFMT_NOFILE))
    {
        ret = avio_open(&ofmt_ctx->pb, outPutFileName.c_str(), AVIO_FLAG_WRITE);
        if (ret < 0)
        {
            printf("Could not open output file '%s'", outPutFileName.c_str());
            goto end;
        }
    }
    //Write file header
    if (avformat_write_header(ofmt_ctx, NULL) < 0)
    {
        printf("Error occurred when opening output file\n");
        goto end;
    }
    return true;
end:
    closeTransWriter();
    return false;
}

void videoTransWriter::startWriter()
{
    mutex.lock();

    int ret = 0;
    stopFlag = false;

    if (startFrameIndex > endFrameIndex)
    {
        cout << "Frame index out of range!" << endl;
        stopFlag = true;
    }

    int gopSize = ifmt_ctx->streams[0]->codec->gop_size;
    startFrameIndex -= (gopSize+1);
    //起始帧为正数
    startFrameIndex = startFrameIndex>0 ? startFrameIndex : 0;

    //停止符为假且处理帧数小于结束帧号才进行写视频
    while ((!stopFlag)&&(processedFrameNum<=endFrameIndex))
    {
        AVStream *in_stream, *out_stream;
        //Get an AVPacket
        ret = av_read_frame(ifmt_ctx, &pkt);
        if (ret < 0)
            break;
        //判断已处理的帧数是否在控制范围之内，如不在则不写入
        if (checkRangeState(processedFrameNum))
        {
            in_stream = ifmt_ctx->streams[pkt.stream_index];
            out_stream = ofmt_ctx->streams[pkt.stream_index];

            //Convert PTS/DTS
            pkt.pts = av_rescale_q_rnd(writedFrameNum, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.dts = av_rescale_q_rnd(writedFrameNum, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
            pkt.pos = -1;

            //Write
            if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0)
            {
                printf("Error muxing packet\n");
                break;
            }
            printf("Write %8d frames to output file\n", processedFrameNum);
            writedFrameNum++;		//写入视频帧数加1
        }

        av_free_packet(&pkt);
        processedFrameNum++;			//处理帧数加1
    }
    if (videoEndFlag)
        av_write_trailer(ofmt_ctx);

    mutex.unlock();
}

void videoTransWriter::stopWriter()
{
    stopFlag = true;
}

void videoTransWriter::run()
{
    startWriter();
}

void videoTransWriter::closeTransWriter()
{
    avformat_close_input(&ifmt_ctx);
    /* close output */
    if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
        avio_close(ofmt_ctx->pb);
    avformat_free_context(ofmt_ctx);
}

void videoTransWriter::setWriteFrameIndex(int startIndex, int endIndex)
{
    mutex.lock();
    startFrameIndex = startIndex;
    endFrameIndex = endIndex;
    mutex.unlock();
}

bool videoTransWriter::checkRangeState(int frameIndex)
{
    return ((frameIndex >= startFrameIndex) && (frameIndex <= endFrameIndex));
}
